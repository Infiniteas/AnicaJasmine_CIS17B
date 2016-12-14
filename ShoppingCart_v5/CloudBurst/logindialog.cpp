#include <QDebug>

#include "logindialog.h"

/*!
 * \brief LoginDialog::LoginDialog
 * \param parent
 *
 * Login Constructor
 */
LoginDialog::LoginDialog(QWidget *parent) : QGraphicsView(parent)
{

    initialize();
    addText();

    placement();
    actionConnnect();
    createRE();

    //size of dialog box
    setFixedSize(850,550);
    setMinimumSize(800,550);

}


/*!
 * \brief LoginDialog::initialize
 *
 * Initializes QLabels, QPushButtons, and QLineEdits
 */
void LoginDialog::initialize()
{

    cloudBurstLogo = new QLabel(this);
    cloudBurstLogo->setPixmap(QPixmap(":/gfx/images/CloudBurst_Logo.png"));

    loginLabel = new QLabel(this);
    loginUsernameLabel = new QLabel(this);
    loginPasswordLabel = new QLabel(this);

    signUpLabel = new QLabel(this);
    signUpUsernameLabel = new QLabel(this);
    signUpPasswordLabel = new QLabel(this);
    signUpEmailLabel = new QLabel(this);

    passWeak = new QLabel(this);
    passWeak->hide();
    passMedium = new QLabel(this);
    passMedium->hide();
    passStrong = new QLabel(this);
    passStrong->hide();

    errorIconUs = new QLabel(this);
    errorIconUs->setPixmap(QPixmap(":/gfx/images/error.png"));
    errorIconUs->hide();
    errorIconEm = new QLabel(this);
    errorIconEm->setPixmap(QPixmap(":/gfx/images/error.png"));
    errorIconEm->hide();
    errorIconLo = new QLabel(this);
    errorIconLo->setPixmap(QPixmap(":/gfx/images/error.png"));
    errorIconLo->hide();

    loginButton = new QPushButton(this);
    signUpButton = new QPushButton(this);
    cancelButton = new QPushButton(this);
    errorIconPass = new QPushButton(this);
    errorIconPass->setIcon(QIcon(":/gfx/images/error.png"));
    errorIconPass->setStyleSheet("background: transparent;");
    errorIconPass->hide();

    loginUsernameLineEdit = new QLineEdit(this);
    loginPasswordLineEdit = new QLineEdit(this);
    signUpUsernameLineEdit = new QLineEdit(this);
    signUpPasswordLineEdit = new QLineEdit(this);
    signUpEmailLineEdit = new QLineEdit(this);

    passRestHolder = new QLabel(this);
    passRestHolder->setPixmap(QPixmap(":/gfx/images/passRestictions3.png"));
    passRestHolder->hide();

    errorUsernameLabel = new QLabel(this);
    errorUsernameLabel->hide();
    errorPasswordLabel = new QLabel(this);
    errorPasswordLabel->hide();
    errorPassword2Label = new QLabel(this);
    errorPassword2Label->hide();
    errorPassword3Label = new QLabel(this);
    errorPassword3Label->hide();
    errorEmailLabel = new QLabel(this);
    errorEmailLabel->hide();
    errorLoginLabel = new QLabel(this);
    errorLoginLabel->hide();

    viewPassCB = new QCheckBox(this);
    viewPass2CB = new QCheckBox(this);

    emailCheck = new QRegularExpression;
    passCheck = new QRegularExpression;
    passCheck1 = new QRegularExpression;
    passCheck2 = new QRegularExpression;

    red.setColor(QPalette::Base,QColor(255,204,204,255));
    orange.setColor(QPalette::Base, QColor(255,153,102,255));
    yellow.setColor(QPalette::Base, QColor(255,255,153,255));
    green.setColor(QPalette::Base, QColor(204,255,204,255));
    white.setColor(QPalette::Base, Qt::white);

    addText();
}

/*!
 * \brief LoginDialog::addText
 *
 * Set text and font for the QLabels and QPushButtons
 */
void LoginDialog::addText()
{
    QFont font1("Britanna Bold", 20, QFont::Bold, false);
    QFont font2("BritannaBold", 14, QFont::Light, false);
    QFont font3("Britanna Bold",10, QFont::Light, true);
    QFont font4("Britanna Bold",10, QFont::Light, false);

    loginLabel->setText("Login");
    loginLabel->setFont(font1);

    loginUsernameLabel->setText("Username:");
    loginUsernameLabel->setFont(font2);

    loginPasswordLabel->setText("Password:");
    loginPasswordLabel->setFont(font2);

    signUpLabel->setText("Create Account");
    signUpLabel->setFont(font1);

    signUpEmailLabel->setText("Email:");
    signUpEmailLabel->setFont(font2);

    signUpUsernameLabel->setText("Username:");
    signUpUsernameLabel->setFont(font2);

    signUpPasswordLabel->setText("Password:");
    signUpPasswordLabel->setFont(font2);

    errorUsernameLabel->setText("Username is already taken");
    errorUsernameLabel->setFont(font3);
    //set text color red
    errorUsernameLabel->setStyleSheet("color: red");

    errorPasswordLabel->setText("1 Alphabet");
    errorPasswordLabel->setFont(font2);
    //set text color red
    errorPasswordLabel->setStyleSheet("color: red");

    errorPassword2Label->setText("1 Number");
    errorPassword2Label->setFont(font2);
    //set text color red
    errorPassword2Label->setStyleSheet("color: red");

    errorPassword3Label->setText("Min. 8 Chars");
    errorPassword3Label->setFont(font2);
    //set text color red
    errorPassword3Label->setStyleSheet("color: red");

    errorEmailLabel->setText("Invalid Email");
    errorEmailLabel->setFont(font3);
    //set color text red
    errorEmailLabel->setStyleSheet("color: red");

    errorLoginLabel->setText("Invalid Username/Password");
    errorLoginLabel->setFont(font3);
    //set color text red
    errorLoginLabel->setStyleSheet("color: red");

    passWeak->setText("Weak");
    passWeak->setFont(font4);
    passWeak->setStyleSheet("color: orange");

    passMedium->setText("Medium");
    passMedium->setFont(font4);
    passMedium->setStyleSheet("color: #f4e32a");

    passStrong->setText("Strong");
    passStrong->setFont(font4);
    passStrong->setStyleSheet("color: #72e14f");

    loginButton->setText("Login");
    loginButton->setFont(font2);

    signUpButton->setText("Sign Up");
    signUpButton->setFont(font2);

    cancelButton->setText("Cancel");
    cancelButton->setFont(font2);

    viewPassCB->setText("Show Password");
    viewPassCB->setFont(font4);
    viewPass2CB->setText("Show Password");
    viewPass2CB->setFont(font4);

    //sets text on password lines as dots
    loginPasswordLineEdit->setEchoMode(QLineEdit::Password);
    signUpPasswordLineEdit->setEchoMode(QLineEdit::Password);
}


/*!
 * \brief LoginDialog::placement
 *
 * Uses setGeometry() to set absolute positon
 * of each item
 */
void LoginDialog::placement()
{
    //logo placement
    cloudBurstLogo->setGeometry(275,20,250,150);

    //login placement
    loginLabel->setGeometry(50,170,100,50);
    errorIconLo->setGeometry(50,220,20,20);
    errorLoginLabel->setGeometry(70,220,220,20);
    loginUsernameLabel->setGeometry(50,227,120,50);
    loginUsernameLineEdit->setGeometry(170,245,150,20);
    loginPasswordLabel->setGeometry(50,285,120,20);
    loginPasswordLineEdit->setGeometry(170,287,150,20);
    viewPassCB->setGeometry(170,310,200,35);
    loginButton->setGeometry(130,410,100,35);

    //sign up placement
    signUpLabel->setGeometry(430,170,300,50);
    errorIconEm->setGeometry(430,220,20,20);
    errorEmailLabel->setGeometry(450,220,100,20);
    signUpEmailLabel->setGeometry(430,227,60,50);
    signUpEmailLineEdit->setGeometry(555,244,150,20);
    errorIconUs->setGeometry(430,265,20,20);
    errorUsernameLabel->setGeometry(430,265,220,20);
    signUpUsernameLabel->setGeometry(430,285,120,20);
    signUpUsernameLineEdit->setGeometry(555,285,150,20);
    signUpPasswordLabel->setGeometry(430,330,150,20);
    signUpPasswordLineEdit->setGeometry(555,330,150,20);
    viewPass2CB->setGeometry(555,350,200,35);
    signUpButton->setGeometry(515,410,100,35);

    passWeak->setGeometry(725,330,50,20);
    passMedium->setGeometry(720,330,65,20);
    passStrong->setGeometry(720,330,65,20);

    errorIconPass->setGeometry(720,332,20,20);
    errorPasswordLabel->setGeometry(630,390,350,30);
    errorPassword2Label->setGeometry(630,440,350,30);
    errorPassword3Label->setGeometry(630,480,450,30);
    passRestHolder->setGeometry(601,355,180,180);

    //cancel placement
    cancelButton->setGeometry(325,450,100,35);

}

/*!
 * \brief LoginDialog::actionConnnect
 *
 * Connects actions using slots and signals
 */
void LoginDialog::actionConnnect()
{
    connect(viewPassCB, SIGNAL(stateChanged(int)), this, SLOT(showPass(int)));
    connect(signUpEmailLineEdit, SIGNAL(editingFinished()), this, SLOT(validateEmail()));
    connect(signUpPasswordLineEdit, SIGNAL(editingFinished()), this, SLOT(validatePass()));
    connect(viewPass2CB, SIGNAL(stateChanged(int)), this, SLOT(showPass2(int)));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(close()));
    connect(signUpButton, SIGNAL(clicked()), this, SLOT(signUp()));
    connect(loginButton, SIGNAL(clicked()), this, SLOT(login()));
}

/*!
 * \brief LoginDialog::createRE
 *
 * Creates Regular Expressons to check
 * correct formatting for email and password
 */
void LoginDialog::createRE()
{
    emailCheck->setPattern("^[0-9a-zA-Z]+([0-9a-zA-Z]*[-._+])*[0-9a-zA-Z]+@[0-9a-zA-Z]+([-.][0-9a-zA-Z]+)*([0-9a-zA-Z]*[.])[a-zA-Z]{2,6}$");

    //Minimum 8 characters at least 1 Alphabet and 1 Number:
    passCheck->setPattern("^(?=.*[A-Za-z])(?=.*\\d)[A-Za-z\\d$@$!%*?&]{8,}$");

    //Minimum 8 characters at least 1 Uppercase Alphabet, 1 Lowercase Alphabet and 1 Number:
    passCheck1->setPattern("^(?=.*[a-z])(?=.*[A-Z])(?=.*\\d)[a-zA-Z\\d]{8,}$");

    //Minimum 8 characters at least 1 Uppercase Alphabet, 1 Lowercase Alphabet, 1 Number and 1 Special Character:
    passCheck2->setPattern("^(?=.*[a-z])(?=.*[A-Z])(?=.*\\d)(?=.*[$@$!%*?&])[A-Za-z\\d$@$!%*?&]{8,}");
}

/*!
 * \brief LoginDialog::showPass
 * \param check
 *
 * Displays password or hides it
 */
void LoginDialog::showPass(int check)
{
    if (check == 2)
    {
        loginPasswordLineEdit->setEchoMode(QLineEdit::Normal);
    }
    else
    {
        loginPasswordLineEdit->setEchoMode(QLineEdit::Password);
    }
}

/*!
 * \brief LoginDialog::showPass2
 * \param check
 *
 * Displays password or hides it
 */
void LoginDialog::showPass2(int check)
{
    if (check == 2)
    {
        signUpPasswordLineEdit->setEchoMode(QLineEdit::Normal);
    }
    else
    {
        signUpPasswordLineEdit->setEchoMode(QLineEdit::Password);
    }
}

/*!
 * \brief LoginDialog::validateEmail
 *
 * Validates email format
 */
void LoginDialog::validateEmail()
{
    if(!emailCheck->match(signUpEmailLineEdit->text()).hasMatch())
    {
        errorIconEm->show();
        errorEmailLabel->show();
        signUpEmailLineEdit->setPalette(red);

    }
    else
    {
        errorIconEm->hide();
        errorEmailLabel->hide();
        signUpEmailLineEdit->setPalette(white);

    }

}

/*!
 * \brief LoginDialog::validatePass
 *
 * Validates password format
 */
void LoginDialog::validatePass()
{
    if(!passCheck->match(signUpPasswordLineEdit->text()).hasMatch())
    {
        signUpPasswordLineEdit->setPalette(red);
        errorIconPass->show();
        passRestHolder->show();
        errorPasswordLabel->show();
        errorPassword2Label->show();
        errorPassword3Label->show();
        passWeak->hide();
        passMedium->hide();
        passStrong->hide();

    }
    else
    {
        errorIconPass->hide();
        errorPasswordLabel->hide();
        passRestHolder->hide();
        passRestHolder->hide();
        errorPasswordLabel->hide();
        errorPassword2Label->hide();
        errorPassword3Label->hide();

        if(passCheck2->match(signUpPasswordLineEdit->text()).hasMatch())
        {
            passWeak->hide();
            passMedium->hide();
            passStrong->show();
            signUpPasswordLineEdit->setPalette(green);
        }
        else if(passCheck1->match(signUpPasswordLineEdit->text()).hasMatch())
        {
            passWeak->hide();
            passStrong->hide();
            passMedium->show();
            signUpPasswordLineEdit->setPalette(yellow);
        }
        else
        {
            passStrong->hide();
            passMedium->hide();
            passWeak->show();
            signUpPasswordLineEdit->setPalette(orange);

        }

    }

}


/*!
 * \brief LoginDialog::changeEmColor
 *
 * Changes email QLineEdit background color
 *
 */
void LoginDialog::changeEmColor()
{
    signUpEmailLineEdit->setPalette(white);
}

/*!
 * \brief LoginDialog::signUp
 *
 * Emits a signal after login has ended
 */
void LoginDialog::signUp()
{
    emit loginEnded();
}

/*!
 * \brief LoginDialog::login
 *
 * Emits a signal after login has ended
 */
void LoginDialog::login()
{
    emit loginEnded();
}







