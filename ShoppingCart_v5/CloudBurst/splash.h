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

public:
    Splash(QWidget *parent = 0);
    ~Splash();
    void paintEvent(QPaintEvent* event);

    QMovie *holiday; //splash gif

public slots:
    void frameUpdate();
    void deleteSplash();


};

#endif // SPLASH_H
