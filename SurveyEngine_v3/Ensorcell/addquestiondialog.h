#ifndef ADDQUESTIONDIALOG_H
#define ADDQUESTIONDIALOG_H

#include "ElementDialog.h"

#include <QDialog>
#include <QWidget>
#include <QSignalMapper>
#include <QPushButton>
#include <QComboBox>
#include <QLineEdit>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QRadioButton>
#include <QCheckBox>


class AddQuestionDialog : public QDialog {
    Q_OBJECT

public:
    AddQuestionDialog(QWidget *parent = 0);
    ~AddQuestionDialog();

    void createElementComboBox();
    void createButtons();
    void createQuestionOptions();
    void createQuestion();

    int choice;
    int spinBoxValue;
    int elementType;

    QPushButton *addQ;                  //adds question
    QPushButton *addE;                  //adds elements
    QLineEdit *questionTextLineEdit;    //user inputs question
    QPushButton *cancelQ;           //cancels the addition of a question
    QComboBox *elementTypes;        //choose element type to add to question
    QLabel *questionLabel;         //shows question number
    QLabel *questionNumber;         //shows question number
    QVBoxLayout *questionDialogLayout;  //main layout
    ElementDialog *addElement;          //element dialog appears
    QSignalMapper *elementMapper;       //maps element signals and slots
    QRadioButton *radButton[20];       //radiobutton array
    QCheckBox *checkButton[20];
    QLineEdit *buttonLineEdit[20];     //line edit array to hold label edits
    QSignalMapper *elementLabelMapper;  //maps line edit signals and slots


public slots:
    void addQuestion();
    void addElements();
    void elementClicked(int elementNum);
    void elementLEClicked(int lENum);
    void setElementType(int type);
    void isElementDialogFinished(int result);

};

#endif // ADDQUESTIONDIALOG_H


