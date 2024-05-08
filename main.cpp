
#include "mainwindow.h"

#include <QApplication>
#include <QSharedMemory>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    const QString mutexName = "UniqueMutex";

    QSharedMemory mutex;
    mutex.setKey(mutexName);

    if (!mutex.create(1)) {
        QMessageBox::critical(nullptr, "Error", "Another instance of the application is already running.");
        return -1;
    }

    MainWindow w;
    w.show();

    return a.exec();
}
