#include "ElementDialog.h"

/*!
 * \brief ElementDialog::ElementDialog
 * \param parent
 *
 * ElementDialog Contructor
 */
ElementDialog::ElementDialog(QWidget *parent) : QDialog(parent)
{
    initialize();
    createLayoutComboBox();
    createElementOptions();

    setLayout(elementDialogLayout);
    setFixedSize(300,150);
}

/*!
 * \brief ElementDialog::~ElementDialog
 *
 * Elemnt Dialog Deconstructor
 */
ElementDialog::~ElementDialog()
{
    delete elementAmountLabel;
    delete elementAmountLineEdit;
    delete addElement;
    delete cancelElement;
    delete spinBox;
    delete layoutChoice;
    delete elementDialogLayout;
}

/*!
 * \brief ElementDialog::createLayoutComboBox
 *
 * Creates the Combobox of the layout choices
 */
void ElementDialog::createLayoutComboBox()
{
    layoutChoice->addItem("Choose Layout");
    layoutChoice->addItem("Vertical Layout");
    layoutChoice->addItem("Horizontal Layout");
}

/*!
 * \brief ElementDialog::createElementOptions
 *
 * Creates the options presented to the user
 * and adds them into layouts
 */
void ElementDialog::createElementOptions()
{
    elementAmountLabel->setWordWrap(true);
    spinBox->setRange(0, 20);
    spinBox->setValue(2);
    spinBox->setMinimumSize(10,40);
    spinBox->setStyleSheet("font: 15pt;");

    connect(cancelElement, SIGNAL(clicked()), this, SLOT(close()));
    connect(addElement, SIGNAL(clicked()), this, SLOT(accept()));
    connect(layoutChoice,SIGNAL(activated(int)),this,SLOT(setChoice(int)));

    QVBoxLayout *elementQLayout = new QVBoxLayout;
    elementQLayout->addWidget(elementAmountLabel);
    elementQLayout->addWidget(spinBox);

    QVBoxLayout *buttonLayout = new QVBoxLayout;
    buttonLayout->addWidget(addElement);
    buttonLayout->addWidget(cancelElement);

    QHBoxLayout *rows = new QHBoxLayout;
    rows->addLayout(elementQLayout);
    rows->addLayout(buttonLayout);

    elementDialogLayout->addLayout(rows);
    elementDialogLayout->addWidget(layoutChoice);

}

/*!
 * \brief ElementDialog::initialize
 *
 * Initializes the variables
 */
void ElementDialog::initialize()
{
    //initial main layout
    elementDialogLayout = new QVBoxLayout;

    //initialize Combo box
    layoutChoice = new QComboBox;

    //initialize Labels
    elementAmountLabel = new QLabel(tr("Desired amount of elements added to question?"));

    //initialize Line Edit
    elementAmountLineEdit = new QLineEdit;

    //initialize Buttons
    addElement = new QPushButton("Add");
    addElement->setEnabled(false);
    cancelElement = new QPushButton("Cancel");

    //initialize Spin box
    spinBox = new QSpinBox;
}

/*!
 * \brief ElementDialog::setChoice
 * \param selectedChoice
 *
 * Saves the choice of the combobox
 */
void ElementDialog::setChoice(int selectedChoice)
{
    choice = selectedChoice;
    spinBoxValue = spinBox->value();

   addElement->setEnabled(true);
}
