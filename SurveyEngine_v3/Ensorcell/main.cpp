#include <QApplication>

#include "mainwindow.h"
#include "splash.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Splash *splash = new Splash;
    splash->show();

    MainWindow *w = new MainWindow;

    QTimer::singleShot(9000,splash,SLOT(close()));
    QTimer::singleShot(9000,w,SLOT(showLogin()));

    return a.exec();
}
