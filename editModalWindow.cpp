#include "editModalWindow.h"
#include "ui_editmodalwindow.h"

#include "csvFileController.h"

editModalWindow::editModalWindow(std::list<Application>& list, MainWindow* mainWindow, QWidget *parent)
    : QDialog(parent),
    appsList(&list),
    ui(new Ui::editModalWindow),
    mainWindow(mainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Edit Your List");
    setAppListInLabel();
}

editModalWindow::~editModalWindow()
{
    delete ui;
}

bool editModalWindow::deleteAppFromlist(const QString& appName) {
    bool found = false;

    auto it = appsList->begin();
    while (it != appsList->end()) {
        if (appName == it->appName) {
            appsList->erase(it);
            found = true;
            break;
        }
        else ++it;
    }
    return found;
}

void editModalWindow::setAppListInLabel() {
    QString appsNameOutput;
    ui->appsOutputLabel->clear();
    for (auto& app : *appsList) {
        appsNameOutput.append(app.appName + "\n");
    }
    MainWindow::setLabelText(ui->appsOutputLabel, appsNameOutput);
}

QString editModalWindow::setBlacklistInLabel(QLabel* label) {
    QString appsNameOutput;
    label->clear();
    std::vector<std::string> blacklistContent = CSVController::readCSVFile("blacklist.csv", "AppName; NewAppName("" - blocked)\n");
    for (size_t i = 5; i < blacklistContent.size(); ++i) {
        std::istringstream ss(blacklistContent[i]);
        std::vector<QString> parts;
        std::string part;

        while (std::getline(ss, part, ';')) {
            parts.push_back(QString::fromStdString(part).trimmed());
        }
        if (parts[1].isEmpty()) {
            appsNameOutput.append(parts[0] + "\n");
        }
    }
    MainWindow::setLabelText(label, appsNameOutput);
    return appsNameOutput;
}

bool editModalWindow::deleteFromLogs(const QString& appName) {
    bool found = deleteAppFromlist(appName);

    if (found) {
        try {
            CSVController::deleteFromlogs(appName.toStdString());
        } catch (std::exception& err) {
            qDebug() << err.what();
            return -1;
        }
    } else return 0;
    return 1;
}

int editModalWindow::changeNameInLogs(const QString& appName, const QString& newAppName) {
    bool found = deleteAppFromlist(appName);

    if (found) {
        try {
            // 1 - app change 1st time, 2 - app was already changed
            return (CSVController::changeNameInLogs(appName.toStdString(), newAppName.toStdString()) ? 2 : 1);
        } catch (std::exception& err) {
            qDebug() << err.what();
            return -1;
        }
    } else return 0; // 0 - didn't find app in list
}


void editModalWindow::on_deleteAppButton_clicked() {
    QDialog modalWin;
    modalWin.setWindowTitle("Delete");

    QLineEdit* line = new QLineEdit(&modalWin);

    QPushButton* button = new QPushButton("Confirm", &modalWin);

    QLabel* label = new QLabel("Enter App Name to Delete", &modalWin);

    QLabel* errLabel = new QLabel("You entered wrong App Name", &modalWin);

    QLabel* errLabelEmpty = new QLabel("Please enter App Name", &modalWin);

    errLabel->setStyleSheet("color: red");

    errLabel->hide();

    errLabelEmpty->hide();

    errLabelEmpty->setStyleSheet("color: red");

    QObject::connect(button, &QPushButton::clicked, [&modalWin, line, this, errLabel, errLabelEmpty]() {
        QString text = line->text();
        if(text.isEmpty()) errLabelEmpty->show();
        else {
            if (deleteFromLogs(text)) {
                modalWin.close();
                mainWindow->refreshList();
                setAppListInLabel();
            }
            else errLabel->show();
        }
    });

    QVBoxLayout *layout = new QVBoxLayout(&modalWin);
    layout->addWidget(errLabel);
    layout->addWidget(errLabelEmpty);
    layout->addWidget(label);
    layout->addWidget(line);
    layout->addWidget(button);

    modalWin.setLayout(layout);

    modalWin.exec();
}


void editModalWindow::on_refreshListButton_clicked()
{
    mainWindow->refreshList();
    setAppListInLabel();
}


void editModalWindow::on_editAppButton_clicked()
{
    QDialog modalWin;
    modalWin.setWindowTitle("Change Name");

    QLineEdit* line = new QLineEdit(&modalWin);
    QLineEdit* lineChange = new QLineEdit(&modalWin);

    QPushButton* button = new QPushButton("Confirm", &modalWin);

    QLabel* labelApp = new QLabel("Enter App Name to Change", &modalWin);

    QLabel* labelChange = new QLabel("Enter new App Name (Don't use commas ',')", &modalWin);

    QLabel* errLabel = new QLabel("You entered wrong App Name", &modalWin);

    QLabel* errLabelEmpty = new QLabel("Please enter Apps Names", &modalWin);

    QLabel* errLabelSame = new QLabel("App names are the same", &modalWin);


    errLabel->hide();

    errLabelEmpty->hide();

    errLabelSame->hide();

    errLabel->setStyleSheet("color: red");

    errLabelEmpty->setStyleSheet("color: red");

    errLabelSame->setStyleSheet("color: red");

    QObject::connect(button, &QPushButton::clicked, [&modalWin, line, lineChange, this, errLabel, errLabelEmpty, errLabelSame]() {
        QString text = line->text();
        QString textChange = lineChange->text();
        if(text.isEmpty() || textChange.isEmpty()) errLabelEmpty->show();
        else if (text == textChange) errLabelSame->show();
        else {
            int changed = changeNameInLogs(text, textChange);
            if (changed == 1) {
                modalWin.close();
                mainWindow->refreshList();
                setAppListInLabel();
            }
            else if (changed == 2) {
                modalWin.close();
                mainWindow->refreshList();
                deleteAppFromlist(text);
                CSVController::deleteFromlogsNoBlacklist(text.toStdString());
                setAppListInLabel();
            }
            else errLabel->show();
        }
    });

    QVBoxLayout *layout = new QVBoxLayout(&modalWin);
    layout->addWidget(errLabel);
    layout->addWidget(errLabelEmpty);
    layout->addWidget(errLabelSame);
    layout->addWidget(labelApp);
    layout->addWidget(line);
    layout->addWidget(labelChange);
    layout->addWidget(lineChange);
    layout->addWidget(button);

    modalWin.setLayout(layout);

    modalWin.exec();
}


void editModalWindow::on_blacklistEditButton_clicked()
{
    QDialog modalWin;
    modalWin.setWindowTitle("Blacklist");

    QLineEdit* line = new QLineEdit(&modalWin);

    QPushButton* button = new QPushButton("Confirm", &modalWin);

    QLabel* label = new QLabel("Enter App Name to Exclude from Blacklist", &modalWin);

    QLabel* errLabel = new QLabel("You entered wrong App Name", &modalWin);

    QLabel* errLabelEmpty = new QLabel("Please enter App Name", &modalWin);

    QScrollArea* scrollArea = new QScrollArea(&modalWin);
    scrollArea->setWidgetResizable(true); // Allow the scroll area to resize the widget
    QWidget* scrollContent = new QWidget(scrollArea);
    QVBoxLayout* scrollLayout = new QVBoxLayout(scrollContent);

    QLabel* largeLabel = new QLabel("", scrollContent);
    largeLabel->setMinimumSize(450, 300);
    largeLabel->setAlignment(Qt::AlignTop);
    scrollLayout->addWidget(largeLabel);

    QString appsOutput = setBlacklistInLabel(largeLabel);

    errLabel->setStyleSheet("color: red");

    errLabel->hide();

    errLabelEmpty->hide();

    errLabelEmpty->setStyleSheet("color: red");

    QObject::connect(button, &QPushButton::clicked, [&modalWin, line, this, errLabel, errLabelEmpty, appsOutput]() {
        QString text = line->text();
        if(text.isEmpty()) errLabelEmpty->show();
        else if (appsOutput.contains(text)) {
            if (CSVController::deleteFromBlackList(text.toStdString())) {
                modalWin.close();
                mainWindow->refreshList();
                setAppListInLabel();
            }
        } else errLabel->show();
    });

    scrollContent->setLayout(scrollLayout);
    scrollArea->setWidget(scrollContent);

    QVBoxLayout *layout = new QVBoxLayout(&modalWin);
    layout->addWidget(scrollArea);
    layout->addWidget(errLabel);
    layout->addWidget(errLabelEmpty);
    layout->addWidget(label);
    layout->addWidget(line);
    layout->addWidget(button);

    modalWin.setLayout(layout);

    modalWin.exec();
}

