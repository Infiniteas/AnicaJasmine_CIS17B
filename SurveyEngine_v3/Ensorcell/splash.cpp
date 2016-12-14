#include "splash.h"

/*!
 * \brief Splash::Splash
 * \param parent
 *
 * Splash Constructor
 *
 */
Splash::Splash(QWidget *parent) : QSplashScreen(parent)
{
    crystal = new QMovie(":/images/animation/crystal.gif");

    this->setPixmap(QPixmap::fromImage(QImage(":/images/animation/crystal.gif")));
    this->setFocus();
    this->show();

    crystal->start();
    connect(crystal,SIGNAL(updated(QRect)),this,SLOT(frameUpdate()));
}

/*!
 * \brief Splash::paintEvent
 * \param event
 *
 * repaints the pixmap each frameupdate() is called
 */
void Splash::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(crystal->frameRect(), crystal->currentPixmap());
    painter.drawImage(125,155,QImage(":/images/images/ensorcell2.png"));


}

/*!
 * \brief Splash::frameUpdate
 *
 * Updates the frame of the splash
 */
void Splash::frameUpdate()
{
    setPixmap(crystal->currentPixmap());
    update();
}
