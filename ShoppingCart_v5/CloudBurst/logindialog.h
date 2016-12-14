#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QCheckBox>
#include <QAction>
#include <QLabel>
#include <QRegularExpression>
#include <QGraphicsScene>
#include <QPushButton>
#include <QBoxLayout>
#include <QWidget>
#include <QString>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QDebug>


class LoginDialog : public QGraphicsView
{
    Q_OBJECT

public:
    LoginDialog(QWidget *parent = 0);

    QLabel *cloudBurstLogo;
    QLabel *loginLabel;
    QLabel *loginUsernameLabel;
    QLabel *loginPasswordLabel;
    QLabel *signUpLabel;
    QLabel *signUpUsernameLabel;
    QLabel *signUpPasswordLabel;
    QLabel *signUpEmailLabel;
    QLabel *errorUsernameLabel;
    QLabel *errorPasswordLabel;
    QLabel *errorPassword2Label;
    QLabel *errorPassword3Label;
    QLabel *errorEmailLabel;
    QLabel *errorLoginLabel;
    QLabel *passWeak;
    QLabel *passMedium;
    QLabel *passStrong;
    QLabel *passRestHolder;

    QLabel *errorIconUs;

    QLabel *errorIconEm;
    QLabel *errorIconLo;

    QPushButton *loginButton;
    QPushButton *signUpButton;
    QPushButton *cancelButton;
    QPushButton *errorIconPass;

    QLineEdit *loginUsernameLineEdit;
    QLineEdit *loginPasswordLineEdit;
    QLineEdit *signUpUsernameLineEdit;
    QLineEdit *signUpPasswordLineEdit;
    QLineEdit *signUpEmailLineEdit;

    QCheckBox *viewPassCB;
    QCheckBox *viewPass2CB;

    QRegularExpression *emailCheck;
    QRegularExpression *passCheck;
    QRegularExpression *passCheck1;
    QRegularExpression *passCheck2;

    QPalette red;
    QPalette orange;
    QPalette yellow;
    QPalette green;
    QPalette white;

    void initialize();
    void addText();
    void placement();
    void actionConnnect();
    void createRE();
//    void passRest();

public slots:
    void showPass(int);
    void showPass2(int);
    void validateEmail();
    void validatePass();
    void changeEmColor();
    void signUp();
    void login();

signals:
    void loginEnded();


};


#endif // LOGINDIALOG_H

