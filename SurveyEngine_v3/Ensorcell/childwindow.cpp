#include "childwindow.h"

/*!
 * \brief ChildWindow::ChildWindow
 * \param ti
 *
 * ChildWindow Constructor
 */
ChildWindow::ChildWindow(QString ti)
{
    initialize();
    createStatusBar();

    setWidget(centArea);

    title = ti;
    setTitle();

    setMinimumSize(300,300);
    setStyleSheet("background: white;");

}

/*!
 * \brief ChildWindow::setTitle
 *
 * ChildWindow Deconstructor
 *
 */
void ChildWindow::setTitle()
{
    setWindowTitle(title);
}

/*!
 * \brief ChildWindow::createMenu
 *
 * Creates menu for the menu bar
 */
void ChildWindow::createMenu()
{
    menuBarChild = new QMenuBar(centArea);
    menuBarChild->setFixedSize(100,30);
    fileMenu = new QMenu(tr("File"));
    editMenu = new QMenu(tr("Edit"));

    menuBarChild->addMenu(fileMenu);
    menuBarChild->addMenu(editMenu);

    fileMenu->addAction(saveSurvey);

    editMenu->addAction(addQuestion);
    editMenu->addAction(deleteQuestion);

}

/*!
 * \brief ChildWindow::createActions
 *
 * Creates actions and connects them to signals
 * and slots for the menu bar
 */
void ChildWindow::createActions()
{
    addQuestion = new QAction(QIcon(":/images/toolbar/add.png"), tr("Add Question"), this);
    connect(addQuestion, SIGNAL(triggered()), this, SLOT(addQuest()));

    deleteQuestion = new QAction(QIcon(":/images/toolbar/delete_recycle_bin_trash_garbage.png"), tr("Delete Question"), this);
    connect(deleteQuestion, SIGNAL(triggered()), this, SLOT(deleteQuest()));

    saveSurvey = new QAction(QIcon(":/images/toolbar/save.png"), tr("Save Survey"), this);
    saveSurvey->setStatusTip(tr("Save this survey"));
    connect(saveSurvey, SIGNAL(triggered()), this, SLOT(save()));

    saveAsSurvey = new QAction(QIcon(":/images/toolbar/saveAs.png"), tr("Save As..."), this);
    saveAsSurvey->setStatusTip("Save the survey under a new name");
    connect(saveAsSurvey, SIGNAL(triggered()), this, SLOT(saveAs()));
}

/*!
 * \brief ChildWindow::createStatusBar
 *
 * Creates a status bar to alert the user
 * if a file is saved or not
 */
void ChildWindow::createStatusBar()
{
    status = new QStatusBar(this);

    QVBoxLayout *temp = new QVBoxLayout();
    temp->addWidget(status);
    temp->setAlignment(this, Qt::AlignBottom);

    mainLayout->addLayout(temp);

}

/*!
 * \brief ChildWindow::readFile
 * \param fileName
 * \return
 *
 * Reads the file opened
 */
bool ChildWindow::readFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, tr("Survey"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(file.fileName())
                             .arg(file.errorString()));
        return false;
    }

    QDataStream in(&file);
    in.setVersion(QDataStream::Qt_4_3);

    quint32 magic;
    in >> magic;

    if (magic != MagicNumber) {
        QMessageBox::warning(this, tr("Survey"),
                             tr("The file is not a Survey file."));
        return false;
    }



    return true;
}

/*!
 * \brief ChildWindow::writeFile
 * \param fileName
 * \return
 *
 * Write to the file
 */
bool ChildWindow::writeFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::warning(this, tr("Survey"),
                             tr("Cannot write file %1:\n%2.")
                             .arg(file.fileName())
                             .arg(file.errorString()));
        return false;
    }

    QDataStream out(&file);
    out.setVersion(QDataStream::Qt_4_3);

    out << quint32(MagicNumber);

    return true;
}

/*!
 * \brief ChildWindow::initialize
 *
 * Initializes the variables
 */
void ChildWindow::initialize()
{

    centArea = new QWidget;
    mainLayout = new QVBoxLayout(centArea);
    mainLayout->addSpacing(25);
    mainLayout->setAlignment(this, Qt::AlignCenter);
    mainLayout->setSpacing(0);
    createActions();
    createMenu();

    lastVL = new QVBoxLayout;
    lastHL = new QHBoxLayout;

    v = false;
    h = false;

}

/*!
 * \brief ChildWindow::saveFile
 * \param fileName
 * \return
 *
 * Saves the file
 */
bool ChildWindow::saveFile(const QString &fileName)
{
    if (!writeFile(fileName)) {
        status->showMessage(tr("Saving canceled"), 2000);
        return false;
    }


    setCurrentFile(fileName);
    writeFile(fileName);
    status->showMessage(tr("File saved"), 2000);
    return true;
}

/*!
 * \brief ChildWindow::setCurrentFile
 * \param fileName
 *
 * Updates the current file
 */
void ChildWindow::setCurrentFile(const QString &fileName)
{
    curFile = fileName;
    setWindowModified(false);

    QString shownName = tr("Untitled");
    if (!curFile.isEmpty()) {
        shownName = strippedName(curFile);
//        updateRecentFileActions();
    }

    setWindowTitle(tr("%1[*] - %2").arg(shownName)
                                   .arg(tr("Spreadsheet")));
}

/*!
 * \brief ChildWindow::strippedName
 * \param fullFileName
 * \return
 *
 * Saves the name of the file
 */
QString ChildWindow::strippedName(const QString &fullFileName)
{
    return QFileInfo(fullFileName).fileName();
}

/*!
 * \brief ChildWindow::addQuest
 *
 * Creates a new Question Dialog
 * and connects it to a signal that alerts the main
 * window the question is completed
 */
void ChildWindow::addQuest()
{
    qDebug() << "button was clicked";
    newQuest = new AddQuestionDialog;
    newQuest->show();

    connect(newQuest, SIGNAL(finished(int)), this, SLOT(isQuestionDialogFinished(int)));
}

/*!
 * \brief ChildWindow::deleteQuest
 *
 * Deletes the last question added to the survey
 */
void ChildWindow::deleteQuest()
{

    if (lastVL->isEmpty()){
        mainLayout->removeItem(lastHL);
    }
    else
    {
        mainLayout->removeItem(lastVL);

    }

}

/*!
 * \brief ChildWindow::elementClicked
 * \param num
 *
 * Displays which element is clicked
 */
void ChildWindow::elementClicked(int num)
{
    qDebug() << num;
}

/*!
 * \brief ChildWindow::isQuestionDialogFinished
 * \param result
 *
 * Adds the necessary information from the question
 * dialog to the survey mini window
 */
void ChildWindow::isQuestionDialogFinished(int result)
{

    QFont font1("Britanna Bold", 12, QFont::Bold, false);

    if(result == QDialog::Accepted){

        QVBoxLayout *vert = new QVBoxLayout;
        QHBoxLayout *hori = new QHBoxLayout;
        QVBoxLayout *questBL = new QVBoxLayout;

        QLabel *question = new QLabel;
        question->setText(newQuest->questionTextLineEdit->text());
        question->setFont(font1);
        questBL->addWidget(question);

        hori->addLayout(questBL);
        vert->addWidget(question);

//        mainLayout->addWidget(question);

        if (newQuest->elementType == 1 || newQuest->elementType == 2){

           for (int i = 0; i < newQuest->spinBoxValue; i++){

               //removes the line edits
               newQuest->questionDialogLayout->removeWidget(newQuest->buttonLineEdit[i]);

               if (newQuest->choice == 1) {

                   if (newQuest->elementType == 1) {

                        vert->addWidget(newQuest->radButton[i]);
                   } else if (newQuest->elementType == 2) {

                        vert->addWidget(newQuest->checkButton[i]);
                   }
               } else if (newQuest->choice == 2) {
                   if (newQuest->elementType == 1) {

                        hori->addWidget(newQuest->radButton[i]);
                   } else if (newQuest->elementType == 2) {

                        hori->addWidget(newQuest->checkButton[i]);
                   }
               }

           }
        } else if (newQuest->elementType == 3) {

            for (int i = 0; i < newQuest->spinBoxValue; i++){

                if (newQuest->choice == 1) {

                    vert->addWidget(newQuest->buttonLineEdit[i]);

                } else if (newQuest->choice == 2) {

                    hori->addWidget(newQuest->buttonLineEdit[i]);
                }
            }
       }

\

        if (newQuest->choice == 1) {

            mainLayout->addLayout(vert);
            lastVL = vert;
            v = true;
            h = false;

        } else if (newQuest->choice == 2) {

            mainLayout->addLayout(hori);
            lastHL = hori;
            h = true;
            v = false;
        }

        newQuest->close();
        mainLayout->addStretch(10);
    }
    delete status;
    createStatusBar();
}

/*!
 * \brief ChildWindow::save
 * \return
 *
 * Saves the file
 */
bool ChildWindow::save()
{
    if (curFile.isEmpty()) {
        return saveAs();
    } else {
        return saveFile(curFile);
    }
}

/*!
 * \brief ChildWindow::saveAs
 * \return
 *
 * Saves the file under a different name
 */
bool ChildWindow::saveAs()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                               tr("Save Survey"), ".",
                               tr("Survey files (*.su)"));
    if (fileName.isEmpty())
        return false;

    return saveFile(fileName);
}
