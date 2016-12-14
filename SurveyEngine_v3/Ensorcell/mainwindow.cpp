
#include "mainwindow.h"

/*!
 * \brief MainWindow::MainWindow
 *
 * MainWindow Constructor
 */
MainWindow::MainWindow()
{
    login = new LoginDialog;
    connect(login, SIGNAL(loginEnded()), this, SLOT(startSurvey()));

    hide();

    initialize();
    createAction();
    createMenu();

    mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    setCentralWidget(mdiArea);

   move(400,200);
}

/*!
 * \brief MainWindow::~MainWindow
 *
 * MainWindow Deconstructor
 */
MainWindow::~MainWindow()
{

}

/*!
 * \brief MainWindow::createChildWindow
 *
 * Creates each new survey subwindow that is placed
 * inside the MainWindows MDI area
 */
void MainWindow::createChildWindow()
{
    QString number = QString::number(subWindNum);

    QString title = "Survey " + number;

    ChildWindow *subWindow = new ChildWindow(title);
    mdiArea->addSubWindow(subWindow);
    subWindow->show();

    subWindNum++;
}
/*!
 * \brief MainWindow::startSurvey
 *
 * Displays the survey MainWindow after user is
 * finished login
 */
void MainWindow::startSurvey()
{
    this->show();
    login->close();
}

/*!
 * \brief MainWindow::showLogin
 *
 * Displays the LoginDialog
 */
void MainWindow::showLogin()
{
    login->show();
}

/*!
 * \brief MainWindow::createMenu
 *
 * Creates the menus added to the
 * menu bar
 */
void MainWindow::createMenu()
{
    fileMenu = new QMenu("File");

    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newSurvey);
    fileMenu->addAction(openSurvey);
}

/*!
 * \brief MainWindow::createAction
 *
 * Creates QActions and connect the action
 * to signals and slots
 */
void MainWindow::createAction()
{
    newSurvey = new QAction(QIcon(":/images/toolbar/create-icon.png"), tr("Create new Survey"), this);
    openSurvey = new QAction(QIcon(":/images/toolbar/open.png"), tr("Open Survey"), this);

    connect(newSurvey, SIGNAL(triggered()), this, SLOT(createChildWindow()));
}

/*!
 * \brief MainWindow::initialize
 *
 * Initialize variables in the project
 */
void MainWindow::initialize()
{
    mdiArea = new QMdiArea;

    subWindNum = 0;
}

/*!
 * \brief MainWindow::okToContinue
 * \return bool
 *
 * Checks if the subwindow has been altered before
 * making saves
 */
bool MainWindow::okToContinue()
{
    if (isWindowModified()) {
        int r = QMessageBox::warning(this, tr("Survey"),
                        tr("The document has been modified.\n"
                           "Do you want to save your changes?"),
                        QMessageBox::Yes | QMessageBox::No
                        | QMessageBox::Cancel);
        if (r == QMessageBox::Yes) {
            return true;
        } else if (r == QMessageBox::Cancel) {
            return false;
        }
    }
    return true;
}

/*!
 * \brief MainWindow::loadFile
 * \param fileName
 * \return
 *
 * Loads the chosen file
 */
bool MainWindow::loadFile(const QString &fileName)
{
    if (readFile(fileName)) {
        statusBar()->showMessage(tr("Loading canceled"), 2000);
        return false;
    }

    statusBar()->showMessage(tr("File loaded"), 2000);
    return true;
}

/*!
 * \brief MainWindow::readFile
 * \param fileName
 * \return
 *
 * Reads the file chosen
 */
bool MainWindow::readFile(const QString &fileName)
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

    QString str;

    return true;
}

/*!
 * \brief MainWindow::writeFile
 * \param fileName
 * \return
 *
 * Writes to the file
 */
bool MainWindow::writeFile(const QString &fileName)
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
 * \brief MainWindow::open
 *
 * Opens the file
 */
void MainWindow::open()
{
    if (okToContinue()) {
        QString fileName = QFileDialog::getOpenFileName(this,
                                   tr("Open Survey"), ".",
                                   tr("Survey files (*.su)"));
        if (!fileName.isEmpty())
            loadFile(fileName);
    }
}
