#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "editModalWindow.h"

#include <vector>
#include <sstream>
#include <regex>

#include "csvFileController.h"

// Main Window Constructor
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QWidget::setWindowTitle("TimeUsage");
    QIcon icon(":/icon.ico");
    QApplication::setWindowIcon(icon);

    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setIcon(icon);

    QMenu *trayMenu = new QMenu(this);
    QAction *showAction = new QAction("Show", this);
    connect(showAction, &QAction::triggered, this, &MainWindow::showNormal);
    trayMenu->addAction(showAction);

    QAction *exitAction = new QAction("Exit", this);
    connect(exitAction, &QAction::triggered, this, &MainWindow::close);
    trayMenu->addAction(exitAction);

    trayIcon->setContextMenu(trayMenu);

    trayIcon->show();

    connect(trayIcon, &QSystemTrayIcon::activated, this, &MainWindow::trayIconActivated);

    initialCalculation();

    // autoRun = isAutorunEnabled();
    // if (autoRun) ui->autoRunCheckBox->setCheckState(Qt::Checked);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::calculateTimeUsage); // timer every 1s running function calculateTimeUsage
    timer->start(1000);
}

void MainWindow::showEvent(QShowEvent *event) {
    QMainWindow::showEvent(event);

    trayIcon->setVisible(true);
}

void MainWindow::trayIconActivated(QSystemTrayIcon::ActivationReason reason) {
    if (reason == QSystemTrayIcon::DoubleClick) {
        showNormal();
    }
}

void MainWindow::closeEvent(QCloseEvent *event) {
    if (trayIcon->isVisible()) {
        QApplication::quit();
    } else {
        QMainWindow::closeEvent(event);
    }
}

// bool MainWindow::isAutorunEnabled() {
//     QSettings settings("HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Run", QSettings::NativeFormat);
//     QString appPath = QDir::toNativeSeparators(QCoreApplication::applicationFilePath());
//     appPath = "\"" + appPath + "\"";
//     appPath += " -silent";
//     QString appName = QCoreApplication::applicationName();
//     QString regValue = settings.value(appName).toString();
//     return (regValue == appPath);
// }

// Main Window Destructor
MainWindow::~MainWindow()
{
    // add info into log file after programm is closed
    updateLogs();

    delete ui;

    delete trayIcon;

    delete timer;
}

// void MainWindow::setAutorun(int arg) {
//     QSettings settings("HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Run", QSettings::NativeFormat);

//     autoRun = (arg == 0 ? false : true);

//     QString appName = QCoreApplication::applicationName();

//     if (autoRun) {
//         QString appPath = QDir::toNativeSeparators(QCoreApplication::applicationFilePath());
//         appPath = "\"" + appPath + "\"";
//         appPath += " -silent";
//         settings.setValue(appName, appPath);
//     } else {
//         settings.remove(appName);
//     }

//     settings.sync();
// }


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

    std::vector<std::string> blacklistContent = CSVController::readCSVFile("blacklist.csv", "AppName; NewAppName("" - blocked)\n");

    // updating list of apps by comparing to current active apps
    for (auto& app : currentAppsList) {
        bool blacklist = false;
        for (auto& name : blacklistContent) {
            std::istringstream blacklistSs(name);
            std::vector<QString> blacklistParts;
            std::string blacklistPart;

            while (std::getline(blacklistSs, blacklistPart, ';')) {
                blacklistParts.push_back(QString::fromStdString(blacklistPart).trimmed());
            }
            if (blacklistParts[0] == app) {
                blacklist = true;
                break;
            }
        }
        if (blacklist) continue;
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
        readFromLogs();
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

    std::vector<std::string> blacklistContent = CSVController::readCSVFile("blacklist.csv", "AppName; NewAppName("" - blocked)\n");

    // updating list of apps by comparing to current active apps
    for (const auto& app : currentAppsList) {
        bool blacklist = false;
        for (auto& name : blacklistContent) {
            std::istringstream blacklistSs(name);
            std::vector<QString> blacklistParts;
            std::string blacklistPart;

            while (std::getline(blacklistSs, blacklistPart, ';')) {
                blacklistParts.push_back(QString::fromStdString(blacklistPart).trimmed());
            }
            if (blacklistParts[0] == app) {
                blacklist = true;
                break;
            }
        }
        if (blacklist) continue;
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

        std::vector<std::string> blacklistContent = CSVController::readCSVFile("blacklist.csv", "AppName; NewAppName\n");

        QString newTitle = QString::fromStdString(std::regex_replace(title, std::regex("[ ,]+"), "")); // delete spaces and commas in string

        for(auto& line : blacklistContent) {
            std::istringstream ss(line);
            std::vector<QString> parts;
            std::string part;

            while (std::getline(ss, part, ';')) {
                parts.push_back(QString::fromStdString(part).trimmed());
            }
            if (newTitle == parts[0] && !parts[1].isEmpty()) {
                newTitle = parts[1].trimmed();
                break;
            }
        }

        window = newTitle;
    }

    return windows;
}

void MainWindow::readFromLogs() {
    listOfApplications.clear();

    std::vector<std::string> blacklistContent = CSVController::readCSVFile("blacklist.csv", "AppName; NewAppName("" - blocked)\n");

    std::vector<std::string> content = CSVController::readCSVFile();
    for (auto& line : content) {
        std::istringstream ss(line);
        std::vector<QString> parts;
        std::string part;

        while (std::getline(ss, part, ';')) {
            parts.push_back(QString::fromStdString(part).trimmed());
        }
        if (parts[0] == "AppName") continue;
        bool blacklist = false;
        for (auto& name : blacklistContent) {
            std::istringstream blacklistSs(name);
            std::vector<QString> blacklistParts;
            std::string blacklistPart;

            while (std::getline(blacklistSs, blacklistPart, ';')) {
                blacklistParts.push_back(QString::fromStdString(blacklistPart).trimmed());
            }
            if (blacklistParts[0] == parts[0]) {
                blacklist = true;
                break;
            }
        }
        if (blacklist) continue;
        listOfApplications.push_back(Application(parts[0], false, QDateTime::fromString(parts[1], "yyyy-MM-dd hh:mm:ss"),
                                                 QDateTime::fromString(parts[2], "yyyy-MM-dd hh:mm:ss"),
                                                 QTime::fromString(parts[4]).second() + QTime::fromString(parts[4]).minute() * 60 + QTime::fromString(parts[4]).hour() * 3600,
                                                 QTime::fromString(parts[3]).second() + QTime::fromString(parts[3]).minute() * 60 + QTime::fromString(parts[3]).hour() * 3600,
                                                 timeToSeconds(parts[5].toStdString())));
    }
}

void MainWindow::updateLogs() {
    for (auto& existApp : listOfApplications) {
        try {
            int lTime = 0;
            long int total = existApp.totalTime;
            if (existApp.lastSessionTime <= 1 && existApp.sessionTime <= 1 && existApp.totalTime <= 5) break;
            if (existApp.lastSessionTime == 0 || existApp.sessionTime >= 1) {
                lTime = existApp.sessionTime;
                total += existApp.sessionTime;
            } else lTime = existApp.lastSessionTime;
            CSVController::editCSVFile(existApp.appName.toStdString(), existApp.sessionStartTime, existApp.sessionEndTime,
                                       lTime, 0, total);
        } catch (const std::exception& err) {
            ui->statusbar->showMessage(err.what());
        }
    }
}

void MainWindow::refreshList() {
    updateLogs();
    readFromLogs();
}

// void MainWindow::on_autoRunCheckBox_stateChanged(int arg1)
// {
//     setAutorun(arg1);
// }


void MainWindow::on_pushButton_clicked() {
    this->hide();
    trayIcon->show();
}


void MainWindow::on_refreshButton_clicked()
{
    refreshList();
}


void MainWindow::on_editButton_clicked() {
    refreshList();
    editModalWindow eWindow(listOfApplications, this);
    eWindow.exec();
}

