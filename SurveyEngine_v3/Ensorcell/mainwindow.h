#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <QMdiArea>
#include <QMenuBar>
#include <QFileDialog>
#include <QMessageBox>
#include <QStatusBar>
#include <QDebug>
#include <QMenu>

#include "childwindow.h"
#include "addquestiondialog.h"
#include "logindialog.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();
    ~MainWindow();

    LoginDialog *login;

    QMdiArea *mdiArea;

    int subWindNum;
    QWidget *survey;

    QMenu *fileMenu;

    QAction *newSurvey;
    QAction *openSurvey;

    enum {MagicNumber = 0x7F51C883};

    void createMenu();
    void createAction();
    void initialize();
//    void createStatusBar();
    bool okToContinue();
    void open();
    void newFile();
    bool loadFile(const QString &fileName);
    bool readFile(const QString &fileName);
    bool writeFile(const QString &fileName);


public slots:
    void createChildWindow();
    void startSurvey();
    void showLogin();

};

#endif // MAINWINDOW_H

