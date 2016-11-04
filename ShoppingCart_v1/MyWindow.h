#ifndef MYWINDOW_H
#define MYWINDOW_H


#include <QWidget>
#include <QString>
#include <QVector>
#include <QLineEdit>
#include <QLabel>
#include <QComboBox>
#include <QGroupBox>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QAction>
#include <QScrollArea>
#include <QSignalMapper>
#include <QMessageBox>


class MyWindow : public QWidget {

    Q_OBJECT

    QVBoxLayout m_mainLayout;
    QScrollArea m_area;


public:

    MyWindow(QWidget *parent = 0);
    void locateItems();
    void createSearch();
    void displayItems();
    bool isCartEmpty();
    QString calcCartTotalString();
    void createMap();
    float price(QString itemName);

    //creates the list of Labels
    void createAllDepartmentsList();
    void createOfficeProductList();
    void createBookList();
    void createElectronicsList();
    void createVideoGamesList();
    float randomFloatGenerator(float a, float b);

    //sets comboBox choice integer
    void setCBChoice(int comboBoxChoice);

    void recreateMainLayout();
    void recreateSignalMapper();

    QVector<QString> allDepartmentsList;
    QVector<QString> bookList;
    QVector<QString> electronicsList;
    QVector<QString> officeProductList;
    QVector<QString> videoGameList;
    QMap<QString, float> cart;


    QVBoxLayout *mainLayout;

private slots:
    void displayCart();
    void addClicked(QString button);
    void removeClicked(QString button);
    void comboBoxItemClicked(int i);

private:
    QLineEdit *searchLineEdit;
    QComboBox *categoriesComboBox;
    QScrollArea * scroller;
    QPushButton *buttons[36];
    QPushButton *viewCartButton;
    QSignalMapper *signalMapper;
    QMap<QString, float> map;

    int choice;                     //holds comboBox chosen index
};

#endif // MYWINDOW_H
