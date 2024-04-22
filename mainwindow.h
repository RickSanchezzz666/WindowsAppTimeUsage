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
    bool isSession;
    bool isActive = false;

    Application(QString name, bool session = false, QDateTime s = QDateTime().currentDateTime(), QDateTime e = QDateTime(), int t = 0) :
        appName(name), sessionStartTime(s), sessionEndTime(e), sessionTime(t), isSession(session) {}
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

private:
    Ui::MainWindow *ui;

    QTimer *timer;

    QProcess *taskListProcess; // to show processes

    std::list<Application> listOfApplications;

};
#endif // MAINWINDOW_H
