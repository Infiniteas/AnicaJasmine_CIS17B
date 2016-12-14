#include <QApplication>
#include <QTimer>

#include "splash.h"
#include "MyWindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Splash *splash = new Splash;
    splash->show();

    MyWindow *w = new MyWindow;



    QTimer::singleShot(9000, w,SLOT(showLoginDialog()));

    return a.exec();
}
