#include "MyWindow.h"
#include <QApplication>


/* File: Shopping
 *=================================================================
 * Programmer: Jasmine Anica
 *=================================================================
 * Program: A Shopping Cart Program. User can add items to a cart.
 * Program will allow user to view items in cart and delete unwanted
 * items. Program calculates total price of all items in cart.
 *
 */

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyWindow w;

    w.setFixedSize(800,600);
    w.show();
    return a.exec();
}
