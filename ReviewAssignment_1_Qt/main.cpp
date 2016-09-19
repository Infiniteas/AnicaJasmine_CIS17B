#include <QCoreApplication>
#include<iostream>
#include<string>
#include "Table.h"
#include "TableInherited.h"

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    //values that will hold the number of rows and cols
        int rows;
        int cols;

        cout << '\t' << "Entering Review Problem 1" << endl << endl
            << "This program will generate a table with dimensions of rows x (rows + 1)" << endl
            << "and display another table with the sum of both the rows and columns" << endl << endl
            << "Enter number of rows:  ";
        cin >> rows;

        cout << endl;

        //column will always be one value higher
        cols = rows + 1;


        TableInherited tab(rows,cols);

        //creates a pointer to the table with the initial values
        //in the base class
        const int *naugT = tab.getTable();

        cout << "the original table: " << endl;

        //for loop to display the table with the initial values
        //from the base class
        for (int i = 0; i < rows*cols; i++)
        {

            cout << naugT[i] << " ";

            if (i % cols == rows) {
                cout << endl;
            }
        }

        cout << endl;

        const int *augT = tab.getAugTable();

        cout << "the enhanced table: " << endl;

        //for loop to display the table with the row and column sums
        //and the grand total of the table
        for (int i = 0; i < (rows +1)*(cols+1); i++)
        {

            cout << augT[i] << " ";

            if (i % (cols + 1) == rows + 1)
            {
                cout << endl;
            }
        }

        cout << endl;



    return a.exec();
}
