#include "splash.h"

/*!
 * \brief Splash::Splash
 * \param parent
 *
 * Splash Screen Constructor
 *
 */
Splash::Splash(QWidget *parent) : QSplashScreen(parent)
{
    holiday = new QMovie(":/gfx/animation/christmas_shopping.gif");

    this->setPixmap(QPixmap::fromImage(QImage(":/animation/animation/christmas_shopping.gif")));
    this->setFocus();
    this->show();

    holiday->start();
    connect(holiday,SIGNAL(updated(QRect)),this,SLOT(frameUpdate()));
    QTimer::singleShot(10000, this, SLOT(deleteSplash()));

}

/*!
 * \brief Splash::~Splash
 *
 * Splash Screen deconstructor
 *
 */
Splash::~Splash()
{
   delete holiday;
}
/*!
 * \brief Splash::paintEvent
 * \param event
 *
 * repaints the pixmap each time it is called
 */
void Splash::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(holiday->frameRect(), holiday->currentPixmap());
    painter.drawImage(520,200,QImage(":/gfx/images/SplashHolidaySale.png"));
    painter.drawImage(40,40,QImage(":/gfx/images/CloudBurst_Holiday.png"));
}

/*!
 * \brief Splash::frameUpdate
 *
 * Updates the frame of the splash screen
 */

void Splash::frameUpdate()
{
    setPixmap(holiday->currentPixmap());
    update();
}

/*!
 * \brief Splash::deleteSplash
 *
 * Deletes the splash screen after main
 * program is loaded
 *
 */

void Splash::deleteSplash()
{
    delete this;
}
