#include "AddQuestionDialog.h"
#include <QDebug>

/*!
 * \brief AddQuestionDialog::createElementComboBox
 *
 * Creates the element in the comboboxs
 */
void AddQuestionDialog::createElementComboBox()
{
    //initialize combo box
    elementTypes = new QComboBox;

    //adds element types to combo box
    elementTypes->addItem("Select element");
    elementTypes->addItem("Radio Button");
    elementTypes->addItem("Check Box");
    elementTypes->addItem("Text Line");

}

/*!
 * \brief AddQuestionDialog::AddQuestionDialog
 * \param parent
 *
 * AddQuestionDialog Constructor
 */
AddQuestionDialog::AddQuestionDialog(QWidget *parent) : QDialog(parent)
{
    //initialize layout
    questionDialogLayout = new QVBoxLayout();
    questionDialogLayout->setSpacing(0);

    createQuestionOptions();
}


/*!
 * \brief AddQuestionDialog::~AddQuestionDialog
 *
 * AddQuestionDialog Deconstructor
 */
AddQuestionDialog::~AddQuestionDialog()
{
    delete addQ;
    delete questionTextLineEdit;
    delete cancelQ;
    delete elementTypes;
    delete questionLabel;
    delete questionNumber;
    delete questionDialogLayout;
}

/*!
 * \brief AddQuestionDialog::createButtons
 *
 * Create the buttons in this dialog
 */
void AddQuestionDialog::createButtons()
{
    //initialize the buttons
    addQ = new QPushButton(tr("Add Question"));
    cancelQ = new QPushButton(tr("Cancel"));
    addE = new QPushButton(tr("Add Elements"));
    addE->setEnabled(false);

    //closes dialog when cancel button is clicked
    connect(cancelQ, SIGNAL(clicked()), this, SLOT(close()));
    connect(addQ, SIGNAL(clicked()), this, SLOT(accept()));
    connect(addE, SIGNAL(clicked()), this, SLOT(addElements()));

}

/*!
 * \brief AddQuestionDialog::createQuestionOptions
 *
 * Creates the Question options and adds them
 * to the layout
 */
void AddQuestionDialog::createQuestionOptions()
{
    createElementComboBox();
    createButtons();

    //set question label text and size
    questionLabel = new QLabel(tr("Question"));
    questionLabel->setAlignment(Qt::AlignCenter);
    questionLabel->setStyleSheet("font: 16pt;");

    questionTextLineEdit = new QLineEdit;
    questionTextLineEdit->setPlaceholderText("ex: Was the website helpful?");
    questionTextLineEdit->setMinimumWidth(200);
    questionTextLineEdit->setMaximumWidth(400);

    connect(elementTypes,SIGNAL(activated(int)),this,SLOT(setElementType(int)));

    QVBoxLayout *buttonLayout = new QVBoxLayout;
    buttonLayout->addWidget(addQ);
    buttonLayout->addWidget(cancelQ);

    QVBoxLayout *inputQueLayout = new QVBoxLayout;
    inputQueLayout->addWidget(questionLabel);
    inputQueLayout->addWidget(questionTextLineEdit);

    QHBoxLayout *queLayout = new QHBoxLayout;
    queLayout->addLayout(inputQueLayout);
    queLayout->addLayout(buttonLayout);

    QHBoxLayout *elementChoiceLayout = new QHBoxLayout;
    elementChoiceLayout->addWidget(elementTypes);
    elementChoiceLayout->addWidget(addE);

    questionDialogLayout->addLayout(queLayout);
    questionDialogLayout->addLayout(elementChoiceLayout);

    setLayout(questionDialogLayout);
}

/*!
 * \brief AddQuestionDialog::createQuestion
 *
 * Creates and maps out the question
 * after the user has declared each part
 */
void AddQuestionDialog::createQuestion()
{
    elementMapper = new QSignalMapper;
    elementLabelMapper = new QSignalMapper();

    //layouts
    QHBoxLayout *hori = new QHBoxLayout;
    QVBoxLayout *vert = new QVBoxLayout;
    hori->setSpacing(0);
    vert->setSpacing(0);

    for (int i = 0; i < spinBoxValue; i++) {

        if (elementType == 1) {

            //connects radio button to element mapper
            radButton[i] = new QRadioButton;
            elementMapper->setMapping(radButton[i], i);
            connect(radButton[i],SIGNAL(clicked()), elementMapper, SLOT(map()));

            //connects line edit to element label mapper
            buttonLineEdit[i] = new QLineEdit();
            elementLabelMapper->setMapping(buttonLineEdit[i], i);
            connect(buttonLineEdit[i],SIGNAL(textEdited(QString)), elementLabelMapper, SLOT(map()));

            //checks which layout was chosen
            if (choice == 1){

                QHBoxLayout *temp = new QHBoxLayout;
                temp->setSpacing(0);
                temp->addWidget(radButton[i]);
                temp->addWidget(buttonLineEdit[i]);

                vert->addLayout(temp);

            } else if (choice == 2) {

                QVBoxLayout *temp = new QVBoxLayout;
                temp->setSpacing(0);
                temp->addWidget(buttonLineEdit[i]);
                temp->addWidget(radButton[i]);

                hori->addLayout(temp);
            }

        } else if (elementType == 2) {

            //connects radio button to element mapper
            checkButton[i] = new QCheckBox;
            elementMapper->setMapping(checkButton[i], i);
            connect(checkButton[i],SIGNAL(clicked()), elementMapper, SLOT(map()));

            //connects line edit to element label mapper
            buttonLineEdit[i] = new QLineEdit();
            elementLabelMapper->setMapping(buttonLineEdit[i], i);
            connect(buttonLineEdit[i],SIGNAL(textEdited(QString)), elementLabelMapper, SLOT(map()));

            //checks which layout was chosen
            if (choice == 1) {

                QHBoxLayout *temp = new QHBoxLayout;
                temp->setSpacing(0);
                temp->addWidget(checkButton[i]);
                temp->addWidget(buttonLineEdit[i]);

                vert->addLayout(temp);

            } else if (choice == 2) {

                QVBoxLayout *temp = new QVBoxLayout;
                temp->setSpacing(0);
                temp->addWidget(checkButton[i]);
                temp->addWidget(buttonLineEdit[i]);

                hori->addLayout(temp);
            }


        } else if (elementType == 3 ){

            //connects radio button to element mapper
            buttonLineEdit[i] = new QLineEdit;
            elementMapper->setMapping(buttonLineEdit[i], i);
            connect(buttonLineEdit[i],SIGNAL(textEdited(QString)), elementMapper, SLOT(map()));

            //checks which layout was chosen
            if (choice == 1) {

                vert->addWidget(buttonLineEdit[i]);

            } else if (choice == 2) {

                hori->addWidget(buttonLineEdit[i]);
            }
        }
    }

    if (choice == 1) {
      //adds to question dialog widget
      questionDialogLayout->addLayout(vert);
    } else if (choice == 2) {
      //adds widgets to dialog
      questionDialogLayout->addLayout(hori);
    }

    connect(elementMapper, SIGNAL(mapped(int)), this, SLOT(elementClicked(int)));
    connect(elementLabelMapper, SIGNAL(mapped(int)), this, SLOT(elementLEClicked(int)));


}

void AddQuestionDialog::addQuestion()
{
    //not used
}

/*!
 * \brief AddQuestionDialog::addElements
 *
 * Creates an ElementDialog
 */
void AddQuestionDialog::addElements()
{
    addElement = new ElementDialog;
    addElement->show();

    connect(addElement, SIGNAL(finished(int)), this, SLOT(isElementDialogFinished(int)));
}

/*!
 * \brief AddQuestionDialog::elementClicked
 * \param elementNum
 *
 * Displays which element is clicked in the map
 */
void AddQuestionDialog::elementClicked(int elementNum)
{
    qDebug() << elementNum;
}

/*!
 * \brief AddQuestionDialog::elementLEClicked
 * \param lENum
 *
 * Determined how to display the elements back into
 * this Dialog
 */
void AddQuestionDialog::elementLEClicked(int lENum)
{
    qDebug() << lENum;

    QFont font1("Britanna Bold", 12, QFont::Light, false);

    if (elementType == 1) {
        QString label = buttonLineEdit[lENum]->text();
        radButton[lENum]->setText(label);
        radButton[lENum]->setFont(font1);

    } else if (elementType == 2) {
        QString label = buttonLineEdit[lENum]->text();
        checkButton[lENum]->setText(label);
        checkButton[lENum]->setFont(font1);
    }

}

/*!
 * \brief AddQuestionDialog::setElementType
 * \param type
 *
 * Saves users selected element type
 */
void AddQuestionDialog::setElementType(int type)
{
    elementType = type;
    addE->setEnabled(true);
}

/*!
 * \brief AddQuestionDialog::isElementDialogFinished
 * \param result
 *
 * This funcitons is called when the user completed chosing
 * quantity of elements and layout
 */
void AddQuestionDialog::isElementDialogFinished(int result)
{
    if(result == QDialog::Accepted){
       this->spinBoxValue = addElement->spinBoxValue;
       this->choice = addElement->choice;
       addElement->close();
       createQuestion();
    }


}
