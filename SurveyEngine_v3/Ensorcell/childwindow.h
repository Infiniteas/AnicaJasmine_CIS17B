#ifndef CHILDWINDOW_H
#define CHILDWINDOW_H

#include <QMdiSubWindow>
#include <QWidget>
#include <QString>
#include <QMenuBar>
#include <QFileDialog>
#include <QMessageBox>
#include <QStatusBar>
#include <QToolBar>
#include <QStatusBar>
#include <QAction>
#include <QDebug>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include "addquestiondialog.h"

class ChildWindow : public QMdiSubWindow
{
    Q_OBJECT

public:
    ChildWindow(QString);

    AddQuestionDialog *newQuest;

    QString title;

    QMenuBar *menuBarChild;
    QMenu *editMenu;
    QMenu *fileMenu;

    QAction *addQuestion;
    QAction *deleteQuestion;
    QAction *saveSurvey;
    QAction *saveAsSurvey;

    QString curFile;

    QStatusBar *status;

    QWidget *centArea;
    QVBoxLayout *mainLayout;
    QVBoxLayout *lastVL;
    QHBoxLayout *lastHL;

    bool v;
    bool h;

    void createMenu();
    void createActions();
    void createStatusBar();
    bool readFile(const QString &fileName);
    bool writeFile(const QString &fileName);
    bool saveFile(const QString &fileName);
    void setCurrentFile(const QString &fileName);
    void initialize();
    void setTitle();
    QString strippedName(const QString &fullFileName);

    enum {MagicNumber = 0x7F51C883};



public slots:
    void addQuest();
    void deleteQuest();
    void elementClicked(int num);
    void isQuestionDialogFinished(int result);
    bool save();
    bool saveAs();


signals:
    void modified();


};

#endif // CHILDWINDOW_H
