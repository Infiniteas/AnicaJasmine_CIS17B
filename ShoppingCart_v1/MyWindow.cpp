#include "MyWindow.h"
#include <QDebug>


MyWindow::MyWindow(QWidget *parent)
    : QWidget(parent), m_mainLayout(this)
{
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

}

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
    QAction *myAction = searchLineEdit->addAction(QIcon(":/icon/search-icon.png"), QLineEdit::TrailingPosition);

    //connects action to the search icon
    connect(myAction,SIGNAL(triggered()), this,SLOT(close()));

    viewCartButton = new QPushButton;
    viewCartButton->setIcon(QIcon(":/icon/blackCart.png"));

    connect(viewCartButton, SIGNAL(clicked()), this, SLOT(displayCart()));

    //creates a layout to hold the combobox and line edit
    QHBoxLayout *searchLayout = new QHBoxLayout;

    //adds line edit and combo box to the horizontal layout
    searchLayout->addWidget(categoriesComboBox);
    searchLayout->addWidget(searchLineEdit);
    searchLayout->addWidget(viewCartButton);

    //brings the combo box and line edit right next to each other
    searchLayout->setSpacing(0);
    searchLayout->setAlignment(Qt::AlignTop);


    //adds the layout with line edit, button, and combo box
    this->m_mainLayout.addLayout(searchLayout);

    setMinimumSize(800,600);

}

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
        QString filePath = ":/icon/" + temp.at(i) + ".jpg";

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
        QString filePath = ":/icon/" + i.key() + ".jpg";

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

void MyWindow::createMap()
{
    for (int i = 0; i < allDepartmentsList.size(); i++){
        float rand = randomFloatGenerator(1.99F,60.99F);
        map.insert(allDepartmentsList.at(i), rand);
    }

}

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

float MyWindow::randomFloatGenerator(float a, float b)
{
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a + r;
}

void MyWindow::setCBChoice(int comboBoxChoice)
{
    choice = comboBoxChoice;
}

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

void MyWindow::recreateSignalMapper()
{
    //iniatilze signalmapper and connect the button
    signalMapper = new QSignalMapper(this);
}

//handles each button clicked
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

void MyWindow::removeClicked(QString button)
{
    cart.remove(button);
    displayCart();
}

void MyWindow::comboBoxItemClicked(int i)
{
    setCBChoice(i);
    displayItems();
}


