#ifndef ELEMENTDIALOG_H
#define ELEMENTDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSpinBox>

class ElementDialog : public QDialog {
    Q_OBJECT

public:
    ElementDialog(QWidget *parent = 0);
    ~ElementDialog();

    void createLayoutComboBox();
    void createElementOptions();
    void initialize();

    QLabel *elementAmountLabel;     //Asks user how many elements to add
    QLineEdit *elementAmountLineEdit;              //allows user to input int value
    int choice;
    int spinBoxValue;
    QPushButton *addElement;        //adds elements to corresponding question
    QPushButton *cancelElement;
    QSpinBox *spinBox;
    QComboBox *layoutChoice;        //choice of verticl/horizontal layout
    QVBoxLayout *elementDialogLayout;   //main layout

public slots:
    void setChoice(int selectedChoice);

};

#endif // ELEMENTDIALOG_H


