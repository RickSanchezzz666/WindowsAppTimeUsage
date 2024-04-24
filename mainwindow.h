#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QProcess>
#include <QDebug>
#include <QList>
#include <QWindow>
#include <QLabel>
#include <QTimer>
#include <QDateTime>
#include <QTime>

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

    void setLabelText(QLabel* label, const QString& qText); // to set text into labels

    void getActiveProcesses(); // get processes

    std::list<QString> getActiveApps(); // get apps

    void calculateTimeUsage();

    void initialCalculation();

    long int timeToSeconds(const std::string& time);

private:
    Ui::MainWindow *ui;

    QTimer *timer;

    QProcess *taskListProcess; // to show processes

    std::list<Application> listOfApplications;

};
#endif // MAINWINDOW_H
