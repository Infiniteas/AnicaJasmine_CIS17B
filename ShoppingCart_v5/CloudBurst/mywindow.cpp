#include "MyWindow.h"
#include <QDebug>

/*!
 * \brief MyWindow::MyWindow
 * \param parent
 *
 * MyWindow Constructor
 */
MyWindow::MyWindow(QWidget *parent)
    : QWidget(parent), m_mainLayout(this)
{
    hide();

    loginD = new LoginDialog;

    connect(loginD, SIGNAL(loginEnded()), this, SLOT(startShopping()));


    createToolBar();
    createSearch();

    m_mainLayout.addWidget(&m_area);

    recreateMainLayout();
    recreateSignalMapper();


    //creates the item labels and images
    createAllDepartmentsList();
    createOfficeProductList();
    createBookList();
    createElectronicsList();
    createVideoGamesList();

    createMap();

    setFixedSize(800,600);

}

/*!
 * \brief MyWindow::createSearch
 *
 * Creates the Search function line above
 * the item display
 */
void MyWindow::createSearch()
{
    //initialize combo box
    categoriesComboBox = new QComboBox();

    //adds drop down menu from combobox
    categoriesComboBox->addItem(tr("All Departments"));
    categoriesComboBox->addItem(tr("Books"));
    categoriesComboBox->addItem(tr("Electronics"));
    categoriesComboBox->addItem(tr("Office Products"));
    categoriesComboBox->addItem(tr("Video Games"));
    connect(categoriesComboBox,SIGNAL(activated(int)),this,SLOT(comboBoxItemClicked(int)));

    //Search Line Edit
    searchLineEdit = new QLineEdit();
    searchLineEdit->setFocus();
    searchLineEdit->setPlaceholderText("Search Function does not work yet");


    //adds the search icon button within the lineEdit
    QAction *myAction = searchLineEdit->addAction(QIcon(":/gfx/items/search-icon.png"), QLineEdit::TrailingPosition);

    //connects action to the search icon
    connect(myAction,SIGNAL(triggered()), this,SLOT(close()));

    viewCartButton = new QPushButton;
    viewCartButton->setIcon(QIcon(":/gfx/items/blackCart.png"));

    connect(viewCartButton, SIGNAL(clicked()), this, SLOT(displayCart()));

    //add cloudburstlogo
    QLabel *cloudBurstLogo = new QLabel;
    cloudBurstLogo->setPixmap(QPixmap(":/gfx/images/CloudBurst_Logo_small.png"));

    //creates a layout to hold the combobox and line edit
    QHBoxLayout *searchLayout = new QHBoxLayout;

    //adds line edit and combo box to the horizontal layout
    searchLayout->addWidget(cloudBurstLogo);
    searchLayout->addWidget(categoriesComboBox);
    searchLayout->addWidget(searchLineEdit);
    searchLayout->addWidget(viewCartButton);

    //brings the combo box and line edit right next to each other
    searchLayout->setSpacing(0);
    searchLayout->setAlignment(Qt::AlignTop);

    //to show the featured product
    QLabel *holidayFeatured = new QLabel;
    holidayFeatured->setAlignment(Qt::AlignCenter);
    holidayFeatured->setPixmap(QPixmap(":/gfx/items/header-holiday-featured-products.jpg"));

    //adds the layout with line edit, button, and combo box
    this->m_mainLayout.addLayout(searchLayout);
    this->m_mainLayout.addWidget(holidayFeatured);
    this->m_mainLayout.setSpacing(0);

    setMinimumSize(800,600);

}

/*!
 * \brief MyWindow::displayItems
 *
 * Displays items in the scroll bar area
 * within the window
 *
 */
void MyWindow::displayItems()
{
    if(!mainLayout->isEmpty()) {
        recreateMainLayout();
        recreateSignalMapper();
    }

    QVector<QString> temp;

    switch (choice){
    case 0: temp = allDepartmentsList;
       break;
    case 1: temp = bookList;
       break;
    case 2: temp = electronicsList;
       break;
    case 3: temp = officeProductList;
        break;
    case 4: temp = videoGameList;
       break;
    }
    //adds widgets to a QHBoxyLayout
    QHBoxLayout *itemRowLayout = new QHBoxLayout;

    for (int i = 0; i < temp.size(); i++) {

        //a string to create the file path
        QString filePath = ":/gfx/items/" + temp.at(i) + ".jpg";

        //create a label to hold the item image
        QLabel *labelImage = new QLabel;
        labelImage->setAlignment(Qt::AlignCenter);

        //finds correlated price
        float itemPrice = price(temp.at(i));

        QString itemPriceQString;
        itemPriceQString.setNum(itemPrice);

        //create a label to hold the item image
        QLabel *labelPrice = new QLabel;
        labelPrice->setAlignment(Qt::AlignCenter);
        labelPrice->setWordWrap(true);
        labelPrice->setText("$" + itemPriceQString);

        //creates a label that will display the description of the item
        QLabel *label = new QLabel(temp.at(i));
        label->setWordWrap(true);
        label->setAlignment(Qt::AlignCenter);

        //paints image
        QPixmap image(filePath);

        //sets image to label
        labelImage->setPixmap(image);

        //creates a button
        buttons[i] = new QPushButton("Add to Cart", this);
        buttons[i]->setFixedSize(200,30);

        //connects a signal to each button
        signalMapper->setMapping(buttons[i], temp.at(i));
        connect(buttons[i], SIGNAL(clicked()), signalMapper, SLOT(map()));

        //layout to hold item image and layout
        QVBoxLayout *itemLayout = new QVBoxLayout;
        itemLayout->setSpacing(0);

        itemLayout->addWidget(labelImage);
        itemLayout->addWidget(labelPrice);
        itemLayout->addWidget(label);
        itemLayout->addWidget(buttons[i]);

        //adds vertical layout into a horizontal layout
        //to create a row ad column effect
        itemRowLayout->addLayout(itemLayout);

        //will create a new row of QVBoxyLayout
        if (i % 3 == 2) {

            //add's the little layout to the box layout.
            mainLayout->addLayout(itemRowLayout);

            //reintialize the layout to delete the items within
            itemRowLayout = new QHBoxLayout;

        }
    }

     connect(signalMapper, SIGNAL(mapped(QString)), this, SLOT(addClicked(QString)));

}

/*!
 * \brief MyWindow::isCartEmpty
 * \return bool
 *
 * Checks if cart is empty
 */
bool MyWindow::isCartEmpty()
{
    float totalPrice = 0.0F;

    QMap<QString, float>::iterator i;

    for (i = cart.begin(); i != cart.end(); ++i){
        totalPrice += i.value();
    }

    if (totalPrice == 0.0F){
        return true;
    }

    return false;
}

/*!
 * \brief MyWindow::displayCart
 *
 * Displays the cart in the scroll area
 */
void MyWindow::displayCart()
{
    if(!mainLayout->isEmpty()) {

        recreateMainLayout();
        recreateSignalMapper();

    }

    if (isCartEmpty()) {

        //label displays empty cart
        QLabel *emtpyCartLabel = new QLabel("Your Shopping Cart is empty.");

        emtpyCartLabel->setAlignment(Qt::AlignCenter);
        emtpyCartLabel->setStyleSheet("font: 25pt;");

        mainLayout->addWidget(emtpyCartLabel);
    }


    //paints cart image
    QPixmap cartImage(":/icon/blackCart 2.png");

    //create a label to hold the item image
    QLabel *cartImageLabel = new QLabel;

    //sets cart image to label
    cartImageLabel->setPixmap(cartImage);
    cartImageLabel->setAlignment(Qt::AlignCenter);

    //create a label to hold the item image
    QLabel *cartTotalLabel = new QLabel;
    cartTotalLabel->setText("Cart Total: $" + calcCartTotalString());
    cartTotalLabel->setStyleSheet("font: 25pt;");

    //sets cart image to label
    cartTotalLabel->setAlignment(Qt::AlignLeft);


    //adds widgets to a QHBoxyLayout
    QHBoxLayout *cartTotalLayout = new QHBoxLayout;
    cartTotalLayout->addWidget(cartImageLabel);
    cartTotalLayout->addWidget(cartTotalLabel);

    mainLayout->addLayout(cartTotalLayout);


    //adds widgets to a QHBoxyLayout
    QHBoxLayout *itemRowLayout = new QHBoxLayout;

    //iterates through cart map
    QMap<QString, float>::iterator i;

    int num = 0;

    for (i = cart.begin(); i != cart.end(); ++i){

        //a string to create the file path
        QString filePath = ":/gfx/items/" + i.key() + ".jpg";

        //create a label to hold the item image
        QLabel *labelImage = new QLabel;
        labelImage->setAlignment(Qt::AlignCenter);

        //finds correlated price
        float itemPrice = price(i.key());

        QString itemPriceQString;
        itemPriceQString.setNum(itemPrice);

        //create a label to hold the item image
        QLabel *labelPrice = new QLabel;
        labelPrice->setAlignment(Qt::AlignCenter);
        labelPrice->setWordWrap(true);
        labelPrice->setText("$" + itemPriceQString);

        //creates a label that will display the description of the item
        QLabel *label = new QLabel(i.key());
        label->setWordWrap(true);
        label->setAlignment(Qt::AlignCenter);

        //paints image
        QPixmap image(filePath);

        //sets image to label
        labelImage->setPixmap(image);

        //creates a button
        buttons[num] = new QPushButton("Remove Item", this);
        buttons[num]->setFixedSize(200,30);

        //connects a signal to each button
        signalMapper->setMapping(buttons[num], i.key());
        connect(buttons[num], SIGNAL(clicked()), signalMapper, SLOT(map()));

        //layout to hold item image and layout
        QVBoxLayout *itemLayout = new QVBoxLayout;
        itemLayout->setSpacing(0);

        itemLayout->addWidget(labelImage);
        itemLayout->addWidget(labelPrice);
        itemLayout->addWidget(label);
        itemLayout->addWidget(buttons[num]);

        //adds vertical layout into a horizontal layout
        //to create a row ad column effect
        itemRowLayout->addLayout(itemLayout);

        //will create a new row of QVBoxyLayout
        if (num % 3 == 2) {

            //reintialize the layout to delete the items within
            itemRowLayout = new QHBoxLayout;

        }

        //add's the little layout to the box layout.
        mainLayout->addLayout(itemRowLayout);

        num++;
    }

     connect(signalMapper, SIGNAL(mapped(QString)), this, SLOT(removeClicked(QString)));


}

/*!
 * \brief MyWindow::calcCartTotalString
 * \return QString
 *
 * Calculates the total cost of the items
 * inside the cart
 */
QString MyWindow::calcCartTotalString()
{
   float totalPrice = 0.0F;

   QMap<QString, float>::iterator i;

   for (i = cart.begin(); i != cart.end(); ++i){
       totalPrice += i.value();
   }

   //sets the float precison to two decimal places
   totalPrice = ((int)(totalPrice*100.0 + 0.5F)) / 100.0F;

   QString totalPriceQString;
   totalPriceQString.setNum(totalPrice);

   return totalPriceQString;

}
/*!
 * \brief MyWindow::createMap
 *
 * Randomly creates the cost of the items
 * and stores the value in a QList
 */
void MyWindow::createMap()
{
    for (int i = 0; i < allDepartmentsList.size(); i++){
        float rand = randomFloatGenerator(1.99F,60.99F);
        map.insert(allDepartmentsList.at(i), rand);
    }

}

/*!
 * \brief MyWindow::price
 * \param itemName
 * \return float
 *
 * Iterates the QList of prices
 * to return the value of the item
 */
float MyWindow::price(QString itemName)
{
    float price = 0;

    QMap<QString, float>::iterator i;

    for (i = map.begin(); i != map.end(); ++i){
        if (i.key() == itemName){
            price = i.value();
        }
    }

    //sets the float precison to two decimal places
    price = ((int)(price*100.0 + 0.5F)) / 100.0F;

    return price;
}

/*!
 * \brief MyWindow::createAllDepartmentsList
 *
 * Creates of ALL DEPARTMENT QList
 * to display all the items
 *
 */
void MyWindow::createAllDepartmentsList()
{
    allDepartmentsList.insert(0, "Pentel Hi-Polymer Block Eraser");
    allDepartmentsList.insert(1, "BIC Brite Liner Highlighters");
    allDepartmentsList.insert(2, "Zebra F-301 Stainless Steel Retractable Ballpoint Pen");
    allDepartmentsList.insert(3, "Elmer's Disappearing Purple School Glue");
    allDepartmentsList.insert(4, "Office+Style Colored Binder Clips");
    allDepartmentsList.insert(5, "Post-it Super Sticky Notes");
    allDepartmentsList.insert(6, "Scotch Multi-Purpose Scissor");
    allDepartmentsList.insert(7, "Swingline Stapler");
    allDepartmentsList.insert(8, "Universal 32-Size Rubber Bands");
    allDepartmentsList.insert(9,"Lord of the Flies");
    allDepartmentsList.insert(10,"Reviving Ophelia");
    allDepartmentsList.insert(11,"The Brief Wondrous Life of Oscar Wao");
    allDepartmentsList.insert(12,"The Catcher in the Rye");
    allDepartmentsList.insert(13,"The Grapes of Wrath");
    allDepartmentsList.insert(14,"The Odyssey");
    allDepartmentsList.insert(15,"The Picture of Dorian Gray");
    allDepartmentsList.insert(16,"The Scarlet Letter");
    allDepartmentsList.insert(17,"Uncle Tom's Cabin");
    allDepartmentsList.insert(18,"1TB Black My Passport Ultra Portable External Hard Drive");
    allDepartmentsList.insert(19,"Anker PowerCore 10000 Portable Charger");
    allDepartmentsList.insert(20,"Fire TV Stick with Alexa Voice Remote");
    allDepartmentsList.insert(21,"Fitbit Charge 2 Heart Rate + Fitness Wristband");
    allDepartmentsList.insert(22,"Fujifilm INSTAX Mini 8 Instant Camera");
    allDepartmentsList.insert(23,"JBL Charge 3 Waterproof Portable Bluetooth Speaker");
    allDepartmentsList.insert(24,"Logitech Wireless Mouse");
    allDepartmentsList.insert(25,"Logitech Wireless USB Keyboard");
    allDepartmentsList.insert(26,"Wireless Bluetooth Headphones");
    allDepartmentsList.insert(27,"Gears of War");
    allDepartmentsList.insert(28,"Half-Life");
    allDepartmentsList.insert(29,"Halo Combat Evolved");
    allDepartmentsList.insert(30,"Left 4 Dead");
    allDepartmentsList.insert(31,"Mario Kart Double Dash");
    allDepartmentsList.insert(32,"Metroid Fusion");
    allDepartmentsList.insert(33,"Portal");
    allDepartmentsList.insert(34,"Super Smash Bros Melee");
    allDepartmentsList.insert(35,"Zelda Ocarina of Time");

}

/*!
 * \brief MyWindow::createOfficeProductList
 *
 * Creates QList office product to
 * display the stationary items
 */
void MyWindow::createOfficeProductList()
{
    officeProductList.insert(0, "Pentel Hi-Polymer Block Eraser");
    officeProductList.insert(1, "BIC Brite Liner Highlighters");
    officeProductList.insert(2, "Zebra F-301 Stainless Steel Retractable Ballpoint Pen");
    officeProductList.insert(3, "Elmer's Disappearing Purple School Glue");
    officeProductList.insert(4, "Office+Style Colored Binder Clips");
    officeProductList.insert(5, "Post-it Super Sticky Notes");
    officeProductList.insert(6, "Scotch Multi-Purpose Scissor");
    officeProductList.insert(7, "Swingline Stapler");
    officeProductList.insert(8, "Universal 32-Size Rubber Bands");
}

/*!
 * \brief MyWindow::createBookList
 *
 * Creates Books QList to display
 * the books
 */
void MyWindow::createBookList()
{
    bookList.insert(0,"Lord of the Flies");
    bookList.insert(1,"Reviving Ophelia");
    bookList.insert(2,"The Brief Wondrous Life of Oscar Wao");
    bookList.insert(3,"The Catcher in the Rye");
    bookList.insert(4,"The Grapes of Wrath");
    bookList.insert(5,"The Odyssey");
    bookList.insert(6,"The Picture of Dorian Gray");
    bookList.insert(7,"The Scarlet Letter");
    bookList.insert(8,"Uncle Tom's Cabin");


}

/*!
 * \brief MyWindow::createElectronicsList
 *
 * Creates Electronic QList to display
 * the electronic devices
 */
void MyWindow::createElectronicsList()
{
    electronicsList.insert(0,"1TB Black My Passport Ultra Portable External Hard Drive");
    electronicsList.insert(1,"Anker PowerCore 10000 Portable Charger");
    electronicsList.insert(2,"Fire TV Stick with Alexa Voice Remote");
    electronicsList.insert(3,"Fitbit Charge 2 Heart Rate + Fitness Wristband");
    electronicsList.insert(4,"Fujifilm INSTAX Mini 8 Instant Camera");
    electronicsList.insert(5,"JBL Charge 3 Waterproof Portable Bluetooth Speaker");
    electronicsList.insert(6,"Logitech Wireless Mouse");
    electronicsList.insert(7,"Logitech Wireless USB Keyboard");
    electronicsList.insert(8,"Wireless Bluetooth Headphones");
}

/*!
 * \brief MyWindow::createVideoGamesList
 *
 * Create the Video Game QList to display
 * the videogames
 */
void MyWindow::createVideoGamesList()
{
    videoGameList.insert(0,"Gears of War");
    videoGameList.insert(1,"Half-Life");
    videoGameList.insert(2,"Halo Combat Evolved");
    videoGameList.insert(3,"Left 4 Dead");
    videoGameList.insert(4,"Mario Kart Double Dash");
    videoGameList.insert(5,"Metroid Fusion");
    videoGameList.insert(6,"Portal");
    videoGameList.insert(7,"Super Smash Bros Melee");
    videoGameList.insert(8,"Zelda Ocarina of Time");
}


/*!
 * \brief MyWindow::randomFloatGenerator
 * \param a
 * \param b
 * \return float
 *
 * Generates and returns a float value
 * betweet values a and b
 */
float MyWindow::randomFloatGenerator(float a, float b)
{
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a + r;
}

/*!
 * \brief MyWindow::setCBChoice
 * \param comboBoxChoice
 *
 * Stores the value of the comboBox chosen
 * (index starts at zero)
 */
void MyWindow::setCBChoice(int comboBoxChoice)
{
    choice = comboBoxChoice;
}

/*!
 * \brief MyWindow::recreateMainLayout
 *
 * Creates the MainLayout of the QWidget
 */
void MyWindow::recreateMainLayout()
{
    //creates a small widget to add layout
    QWidget * contents = new QWidget;

    //creates a layout within the widget
    mainLayout = new QVBoxLayout(contents);

    //sets a size constraint
    mainLayout->setSizeConstraint(QLayout::SetMinimumSize);
    mainLayout->setSpacing(50);

    //adds the widget to the scroll area
    m_area.setWidget(contents);

}

/*!
 * \brief MyWindow::recreateSignalMapper
 *
 * Creates the QSignalMapper that will
 * map out the QPushButton signals
 */
void MyWindow::recreateSignalMapper()
{
    //iniatilze signalmapper and connect the button
    signalMapper = new QSignalMapper(this);
}

/*!
 * \brief MyWindow::createToolBar
 *
 * Creates the toolBar
 */
void MyWindow::createToolBar()
{
    toolBar = new QToolBar;
    createToolActions();

    toolBar->addAction(login);

    QHBoxLayout *barLayout = new QHBoxLayout;
    barLayout->setAlignment(Qt::AlignRight);
    barLayout->addWidget(toolBar);
    m_mainLayout.addLayout(barLayout);
}


/*!
 * \brief MyWindow::createToolActions
 *
 * Creates the actions used in the toolbar
 */
void MyWindow::createToolActions()
{
    login = new QAction;
    login->setText("Login/SignUp");
}

/*!
 * \brief MyWindow::addClicked
 * \param button
 *
 * Iterates through the QSignalMap to
 * see if QPushButton was clicked once
 * and alerts the user that the item
 * is already in the cart
 */
void MyWindow::addClicked(QString button)
{
    bool itemExist = false;

    QMap<QString, float>::iterator i;

    for (i = cart.begin(); i != cart.end(); ++i){
        if (button == i.key()) {
            itemExist = true;
            QMessageBox itemAddedBox;
            itemAddedBox.setText("Item already added to Cart");
            itemAddedBox.exec();
        }
    }

    if (!itemExist) {
       cart.insert(button, price(button));
       QMessageBox itemAddedBox;
       itemAddedBox.setText("Item added to Cart");
       itemAddedBox.exec();
    }

}

/*!
 * \brief MyWindow::removeClicked
 * \param button
 *
 * Deletes the items in the cart
 */
void MyWindow::removeClicked(QString button)
{
    cart.remove(button);
    displayCart();
}


/*!
 * \brief MyWindow::comboBoxItemClicked
 * \param i
 *
 * Uses the combobox index chosen to display
 * the items in the scroll area
 */
void MyWindow::comboBoxItemClicked(int i)
{
    setCBChoice(i);
    displayItems();
}

/*!
 * \brief MyWindow::showLoginDialog
 *
 * Allows the LoginDialog QWidget to be seen
 * after the splash screen ends
 */
void MyWindow::showLoginDialog()
{
    loginD->show();
}

/*!
 * \brief MyWindow::startShopping
 * Starts the ShoppingCart after user logs in
 *
 */
void MyWindow::startShopping()
{
    show();
    loginD->close();
}



