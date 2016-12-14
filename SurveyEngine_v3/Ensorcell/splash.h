#ifndef SPLASH_H
#define SPLASH_H

#include <QSplashScreen>
#include <QPainter>
#include <QMovie>
#include <QTimer>
#include <QFont>
#include <QPen>

class Splash : public QSplashScreen
{
    Q_OBJECT
private:
    QString version;

public:
    Splash(QWidget *parent = 0);
    void paintEvent(QPaintEvent* event);

    QMovie *crystal; //splash gif

public slots:
    void frameUpdate();

};

#endif // SPLASH_H

