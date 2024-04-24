#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <vector>
#include <sstream>

#include "csvFileController.h"

// Main Window Constructor
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QWidget::setWindowTitle("TimeUsage");
    initialCalculation();

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::calculateTimeUsage); // timer every 1s running function calculateTimeUsage
    timer->start(1000);
}

// Main Window Destructor
MainWindow::~MainWindow()
{

    // add info into log file after programm is closed
    for (auto& existApp : listOfApplications) {
        try {
            int lTime = 0;
            int total = existApp.totalTime;
            if (existApp.lastSessionTime <= 1 && existApp.sessionTime <= 1 && existApp.totalTime <= 5) break;
            if (existApp.lastSessionTime == 0 || existApp.sessionTime >= 1) {
                lTime = existApp.sessionTime;
            } else lTime = existApp.lastSessionTime;
            total += (existApp.sessionTime <= 1 ? 0 : lTime);
            CSVController::editCSVFile(existApp.appName.toStdString(), existApp.sessionStartTime, existApp.sessionEndTime,
                lTime, 0, total);
        } catch (const std::exception& err) {
            ui->statusbar->showMessage(err.what());
        }
    }

    delete ui;

    if (taskListProcess) {
        taskListProcess->kill();
        taskListProcess->waitForFinished();
        delete taskListProcess;
    }
}

long int MainWindow::timeToSeconds(const std::string& time) {
    size_t pos = time.find(":");
    std::string hourStr = time.substr(0, pos);
    std::string minuteStr = time.substr(pos + 1);

    int hours = std::stoi(hourStr);
    int minutes = std::stoi(minuteStr);

    return hours * 3600 + minutes * 60;
}

void MainWindow::initialCalculation() {
    std::list<QString> currentAppsList = getActiveApps();

    // updating list of apps by comparing to current active apps
    for (auto& app : currentAppsList) {
        bool isAppExist = false;
        for (auto& existApp : listOfApplications) {
            if (existApp.appName == app) {
                isAppExist = true;
                break;
            }
        }
        if (!isAppExist) listOfApplications.push_back(Application(app, true));
    }

    // check if log file is empty, then add current list of applications into log file
    // else update log file up to current list of applications
    if (CSVController::isLogsFileEmpty()) {
        for (auto& existApp : listOfApplications) {
            try {
                CSVController::editCSVFile(existApp.appName.toStdString(), existApp.sessionStartTime, existApp.sessionEndTime,
                    existApp.lastSessionTime, existApp.sessionTime, existApp.totalTime);
            } catch (const std::exception& err) {
                ui->statusbar->showMessage(err.what());
            }
        }
    } else {
        std::vector<std::string> content = CSVController::readCSVFile();
        for (auto& line : content) {
            bool found = false;
            std::istringstream ss(line);
            std::vector<QString> parts;
            std::string part;

            while (std::getline(ss, part, ';')) {
                parts.push_back(QString::fromStdString(part).trimmed());
            }
            for (auto& existApp : listOfApplications) { // find if current app is in log file, then update existed info
                size_t foundApp = line.find(existApp.appName.toStdString());
                if (foundApp != std::string::npos) {
                    existApp.sessionStartTime = QDateTime::fromString(parts[1], "yyyy-MM-dd hh:mm:ss");
                    existApp.sessionEndTime = QDateTime::fromString(parts[2], "yyyy-MM-dd hh:mm:ss");
                    existApp.lastSessionTime = QTime::fromString(parts[3]).second() + QTime::fromString(parts[3]).minute() * 60 + QTime::fromString(parts[3]).hour() * 3600;
                    existApp.sessionTime = QTime::fromString(parts[4]).second() + QTime::fromString(parts[4]).minute() * 60 + QTime::fromString(parts[4]).hour() * 3600;
                    existApp.totalTime += timeToSeconds(parts[5].toStdString());
                    found = true;
                }
            }
            if (!found) { // if app doesn't exist in log file, then we creating it
                if (parts[0] == "AppName") continue;
                listOfApplications.push_back(Application(parts[0], false, QDateTime::fromString(parts[1], "yyyy-MM-dd hh:mm:ss"),
                    QDateTime::fromString(parts[2], "yyyy-MM-dd hh:mm:ss"),
                    QTime::fromString(parts[4]).second() + QTime::fromString(parts[4]).minute() * 60 + QTime::fromString(parts[4]).hour() * 3600,
                    QTime::fromString(parts[3]).second() + QTime::fromString(parts[3]).minute() * 60 + QTime::fromString(parts[3]).hour() * 3600,
                    timeToSeconds(parts[5].toStdString())));
            }
        }
    }
}

void MainWindow::calculateTimeUsage() {
    std::list<QString> currentAppsList = getActiveApps();

    // make every app in list not active, to update it further on
    for (auto& existApp : listOfApplications) {
        if (existApp.isSession) {
            existApp.isActive = false;
        }
    }

    // updating list of apps by comparing to current active apps
    for (const auto& app : currentAppsList) {
        bool isExist = false;
        for (auto& existApp : listOfApplications) {
            if (app == existApp.appName) {
                isExist = true;
                existApp.isActive = true;
                break;
            }
        }
        if (!isExist) listOfApplications.push_back(Application(app, true));
    }
    QString appsNameOutput;
    QString appsStartTimeOutput;
    QString appsEndTimeOutput;
    QString appsLastTimeOutput;
    QString appsTimeOutput;    
    QString appsTotalTimeOutput;

    ui->appsOutputLabel->clear();
    ui->appsOutputLabel_2->clear();
    ui->appsOutputLabel_3->clear();
    ui->appsOutputLabel_4->clear();
    ui->appsOutputLabel_5->clear();
    ui->appsOutputLabel_6->clear();

    // update info in list of applications
    for (auto& existApp : listOfApplications) {
        if (!existApp.isActive && existApp.isSession) { // app was active, but now it's closed
            existApp.sessionEndTime = QDateTime().currentDateTime();
            existApp.isSession = false;
            existApp.lastSessionTime = existApp.sessionTime;
            existApp.totalTime += existApp.sessionTime;
            existApp.sessionTime = 0;
        } else if (existApp.isActive && !existApp.isSession) { // app active now, but earlier wasn't in session
            existApp.sessionStartTime = QDateTime().currentDateTime();
            existApp.isSession = true;
        } else if (!existApp.isActive && !existApp.isSession); // app and a session was closed
        else { // currently running
            existApp.isSession = true;
            existApp.sessionTime++;
        }

        QTime start(0, 0, 0);
        appsNameOutput.append(existApp.appName + "\n");
        appsStartTimeOutput.append(existApp.sessionStartTime.toString("yyyy-MM-dd HH:mm:ss") + "\n");
        appsEndTimeOutput.append(existApp.sessionEndTime.toString("yyyy-MM-dd HH:mm:ss") + "\n");
        appsTimeOutput.append(start.addSecs(existApp.sessionTime).toString("hh:mm:ss") + "\n");
        appsLastTimeOutput.append(start.addSecs(existApp.lastSessionTime).toString("hh:mm:ss") + "\n");
        appsTotalTimeOutput.append(CSVController::secondsToTime(existApp.totalTime) + "\n");

    }
    setLabelText(ui->appsOutputLabel, appsNameOutput);
    setLabelText(ui->appsOutputLabel_2, appsStartTimeOutput);
    setLabelText(ui->appsOutputLabel_3, appsEndTimeOutput);
    setLabelText(ui->appsOutputLabel_4, appsLastTimeOutput);
    setLabelText(ui->appsOutputLabel_5, appsTimeOutput);
    setLabelText(ui->appsOutputLabel_6, appsTotalTimeOutput);

}

// set text to selected label
void MainWindow::setLabelText(QLabel* label, const QString& qText) {
    label->setText(label->text() + qText);
}

// get active processes of computer
void MainWindow::getActiveProcesses() {
    taskListProcess = new QProcess(this); // creates new process
    ui->appsOutputLabel->clear(); // clear old label before appending info

    connect(taskListProcess, &QProcess::readyReadStandardOutput, this, [this](){ // reading every process
        QString processOutput = taskListProcess->readAllStandardOutput(); // read all output
        setLabelText(ui->appsOutputLabel, processOutput);
    });

    taskListProcess->start("tasklist"); // start process of TaskList reading
}


// get active active apps opened on computer
std::list<QString> MainWindow::getActiveApps() {
    std::list<QString> windows;

    // get every visible window
    EnumWindows([](HWND hwnd, LPARAM lParam) {
        wchar_t title[256];
        if (IsWindowVisible(hwnd) && GetWindowTextW(hwnd, title, sizeof(title) / sizeof(title[0])) > 0) {
            ((std::list<QString>*)lParam)->push_back(QString::fromWCharArray(title));
        }
        return TRUE;
    }, (LPARAM)&windows);

    for (auto& window : windows) {
        QString qTitle = window;
        std::string title = qTitle.toStdString(); // title in std string

        do {
            size_t pos = title.find("-"); // find position of "-" symbol

            if (pos != std::string::npos) { // if "-" is in our string
                title = title.substr(pos + 1); // cut string from pos + 1 to the end
            }
        }
        while (title.find("-") != std::string::npos); // while there are "-" symbol

        QString trimmedTitle = QString::fromStdString(title).trimmed(); // delete spaces in string

        window = trimmedTitle;
    }

    return windows;
}
