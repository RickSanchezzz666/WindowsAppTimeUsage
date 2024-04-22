#include "mainwindow.h"
#include "./ui_mainwindow.h"

// Main Window Constructor
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initialCalculation();
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::calculateTimeUsage);
    timer->start(1000);
}

// Main Window Destructor
MainWindow::~MainWindow()
{
    delete ui;
    if (taskListProcess) { // if taskListProcess is not null, then delete from memory
        taskListProcess->kill();
        taskListProcess->waitForFinished(); // waiting for finished tasks
        delete taskListProcess;
    }
}

void MainWindow::initialCalculation() {
    std::list<QString> currentAppsList = getActiveApps();

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
}

void MainWindow::calculateTimeUsage() {
    std::list<QString> currentAppsList = getActiveApps();

    for (auto& existApp : listOfApplications) {
        if (existApp.isSession) {
            existApp.isActive = false;
        }
    }

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
    QString appsTimeOutput;

    ui->appsOutputLabel->clear();
    ui->appsOutputLabel_2->clear();
    ui->appsOutputLabel_3->clear();
    ui->appsOutputLabel_4->clear();

    for (auto& existApp : listOfApplications) {
        if (!existApp.isActive && existApp.isSession) {
            existApp.sessionEndTime = QDateTime().currentDateTime();
            existApp.isSession = false;
            existApp.sessionTime = 0;
        } else if (existApp.isActive && !existApp.isSession) {
            existApp.sessionStartTime = QDateTime().currentDateTime();
            existApp.isSession = true;
        } else if (!existApp.isActive && !existApp.isSession) continue;
        else {
            existApp.isSession = true;
            existApp.sessionTime++;
        }

        QTime start(0, 0, 0);
        appsNameOutput.append(existApp.appName + "\n");
        appsStartTimeOutput.append(existApp.sessionStartTime.toString("yyyy-MM-dd HH:mm:ss") + "\n");
        appsEndTimeOutput.append(existApp.sessionEndTime.toString("yyyy-MM-dd HH:mm:ss") + "\n");
        appsTimeOutput.append(start.addSecs(existApp.sessionTime).toString("hh:mm:ss") + "\n");

    }
    setLabelText(ui->appsOutputLabel, appsNameOutput);
    setLabelText(ui->appsOutputLabel_2, appsStartTimeOutput);
    setLabelText(ui->appsOutputLabel_3, appsEndTimeOutput);
    setLabelText(ui->appsOutputLabel_4, appsTimeOutput);
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
    std::list<QString> listOFApps;

    HWND hwnd = GetForegroundWindow(); // get top level window

    while (hwnd != NULL) { // while there are windows
        char windowTitle[256]; // max title size
        GetWindowTextA(hwnd, windowTitle, sizeof(windowTitle)); // get window title and put it into windowTitle var

        if (IsWindowVisible(hwnd) && strlen(windowTitle) > 0) { // check if windows is visible and title's size more than 0
            QString qTitle = QString::fromUtf8(windowTitle);
            std::string title = qTitle.toStdString(); // title in std string

            do {
                size_t pos = title.find("-"); // find position of "-" symbol

                if (pos != std::string::npos) { // if "-" is in our string
                    title = title.substr(pos + 1); // cut string from pos + 1 to the end
                }
            }
            while (title.find("-") != std::string::npos); // while there are "-" symbol

            QString trimmedTitle = QString::fromStdString(title).trimmed(); // delete spaces in string

            listOFApps.push_back(trimmedTitle);
        }

        hwnd = GetNextWindow(hwnd, GW_HWNDNEXT); // get new window
    }
    return listOFApps;
}
