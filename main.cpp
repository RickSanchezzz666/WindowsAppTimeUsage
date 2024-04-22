#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv); // main app
    MainWindow window; // main windows
    window.show(); // show main window
    return app.exec();
}
