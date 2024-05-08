#ifndef EDITMODALWINDOW_H
#define EDITMODALWINDOW_H

#include "mainwindow.h"

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QDialog>
#include <QString>
#include <QLabel>

#include <list>

namespace Ui {
class editModalWindow;
}

class editModalWindow : public QDialog
{
    Q_OBJECT

public:
    explicit editModalWindow(std::list<Application>& list, MainWindow* mainWindow = nullptr, QWidget *parent = nullptr);
    ~editModalWindow();

    void setAppListInLabel();

    bool deleteFromLogs(const QString& appName);

    int changeNameInLogs(const QString& appName, const QString& newAppName);

    bool deleteAppFromlist(const QString& appName);

    QString setBlacklistInLabel(QLabel* label);

private slots:
    void on_deleteAppButton_clicked();

    void on_refreshListButton_clicked();

    void on_editAppButton_clicked();

    void on_blacklistEditButton_clicked();

private:
    Ui::editModalWindow *ui;

    std::list<Application>* appsList;

    MainWindow* mainWindow;
};

#endif // EDITMODALWINDOW_H
