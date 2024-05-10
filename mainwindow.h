#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QDebug>
#include <QList>
#include <QWindow>
#include <QLabel>
#include <QTimer>
#include <QDateTime>
#include <QTime>
#include <QSettings>
#include <QDir>
#include <QSystemTrayIcon>
#include <QPushButton>
#include <QCloseEvent>

#include <windows.h>
#include <list>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

struct Application {
    QString appName;
    QDateTime sessionStartTime;
    QDateTime sessionEndTime;
    int sessionTime;
    int lastSessionTime;
    bool isSession;
    bool isActive = false;
    long int totalTime;

    Application(QString name, bool session = false, QDateTime s = QDateTime().currentDateTime(), QDateTime e = QDateTime(), int t = 0, int lT = 0, int total = 0) :
        appName(name), sessionStartTime(s), sessionEndTime(e), sessionTime(t), isSession(session), lastSessionTime(lT), totalTime(total) {}
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    static void setLabelText(QLabel* label, const QString& qText); // to set text into labels

    std::list<QString> getActiveApps(); // get apps

    void calculateTimeUsage();

    void initialCalculation();

    long int timeToSeconds(const std::string& time);

    // void setAutorun(int arg);

    // bool isAutorunEnabled();

    void refreshList();

    void readFromLogs();

    void updateLogs();

    void logsUpdater();

    void trayIconActivated(QSystemTrayIcon::ActivationReason reason);

private slots:
    // void on_autoRunCheckBox_stateChanged(int arg1);

    void on_pushButton_clicked();

    void on_refreshButton_clicked();

    void on_editButton_clicked();

protected:
    void showEvent(QShowEvent *event) override;
    void closeEvent(QCloseEvent *event) override;

private:
    Ui::MainWindow *ui;

    QSystemTrayIcon *trayIcon;

    // bool autoRun = false;

    QTimer *timer;

    QTimer *updateTimer;

    std::list<Application> listOfApplications;

    std::list<QString> appsListNames;

};
#endif // MAINWINDOW_H
