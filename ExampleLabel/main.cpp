/*
 * Author:  Dr. Mark E. Lehr
 * Date:    September 7, 2016
 * Purpose:  Template for Windowed Program
 */

//System Libraries
#include <QApplication>
#include <QLabel>
#include <QString>

//User Libraries
#include<iostream>
#include<string>
#include<sstream>
#include "Table.h"
#include "TableInherited.h"
using namespace std;

//Global Constants

//Function Prototypes

//Execution Begins Here!
int main(int argc, char *argv[]){

    //Declare variables
    int rows = 5;
    int cols = 6;

    string *stringValsTable1 = new string[rows*cols];
    string *stringValsTable2 = new string[(rows + 1)*(cols + 1)];

    string table1 = "";
    string table2 = "";

    //create object
    TableInherited tab(rows,cols);

    //creates a pointer to the table with the initial values
    const int *naugT = tab.getTable();

    //creates a string array from the original table
    for (int i = 0; i < rows*cols; i++) {
            stringValsTable1[i] = to_string(naugT[i]);
    }

    //puts the values in the string array into one string by concatenation
    for (int i = 0; i < rows*cols; i++) {
        table1 += " " + stringValsTable1[i];

        if (i % 6 == 5) {
            table1 += '\n';
        }
    }

    //creates a pointer to the enhanced table
    const int *augT = tab.getAugTable();

    //creates a string array from the original table
    for (int i = 0; i < (rows + 1)*(cols + 1); i++) {
            stringValsTable2[i] = to_string(augT[i]);
    }

    //puts the values in the string array into one string by concatenation
    for (int i = 0; i < (rows + 1)*(cols + 1); i++) {
        table2 += " " + stringValsTable2[i];

        if (i % 7 == 6) {
            table2 += '\n';
        }
    }

    //string titles
    QString tableTitle1("Original 5x6 Table\n");
    QString tableTitle2("\nEnhanced Table with row and column sums\n");

    //turns the std string into a QString
    QString data = QString::fromStdString(table1);
    QString data2 = QString::fromStdString(table2);

    //adds the titles to the corresponding table into one string
    QString firstTable = tableTitle1 + data;
    QString secondTable = tableTitle2 + data2;

    //adds the two table strings into one string
    QString data3 = firstTable + secondTable;

    //Create the Window Application
    QApplication a(argc, argv);
    QLabel *label=new QLabel(data3);


    //Make it visible
    label->show();

    //Exit stage right!
    return a.exec();
}
