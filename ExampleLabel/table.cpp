#include "Table.h"
#include <iostream>
using namespace std;

Table::Table(int r, int c)
{
    //sets the row and col values
    rows = r;
    cols = c;
}

Table::~Table()
{
    delete[] table;
    delete[] rowSum;
    delete[] colSum;
}

void Table::calcTable()
{

    //initialize the grandTotal to zero
    grandTotal = 0;

    //initialize the size of each array
    table = new int[rows*cols];
    rowSum = new int[rows];
    colSum = new int[cols];

    //initialize the row array to zero
    for (int i = 0; i < rows; i++)
    {
        rowSum[i] = 0;
    }
    //initialize the column array to zero
    for (int i = 0; i < cols; i++)
    {
        colSum[i] = 0;
    }

    //initialize the table array to zero
    for (int i = 0; i < rows*cols; i++)
    {
        table[i] = 0;
    }

    //the first value that is entered in the table array
    int values = 100;

    for (int i = 0; i < rows*cols; i++)
    {

        //values are entered into the array
        table[i] = values;

        //values are incremented by 1
        values++;
    }

    //colCounter is used to jump around each column
    int colCounter = 0;

    //for loop to add up the sum of the columns
    for (int i = 0; i < cols; i++)
    {

        //intialize the counter to correspond with the starting index (0-6)
        colCounter = i;

        for (int j = 0; j < rows; j++)
        {

            //adds the total of each column
            colSum[i] += table[colCounter];

            //iterates through the columns
            colCounter += cols;
        }

    }


    //for loop to add up the sum of the rows
    for (int i = 0; i < rows; i++)
    {

        //adjusted to start the index at each row
        for (int j = i * cols; j < ((i*cols) + cols); j++)
        {

            //adds the total of each row
            rowSum[i] += table[j];

        }
    }

    //for loop to add the total sum of each row into the grandTotal
    for (int i = 0; i < rows; i++)
    {
        grandTotal += rowSum[i];
    }

}

Table::Table()
{
    rows = 0;
    cols = 0;
}


const int * Table::getTable()
{
    return table;
}

const int * Table::getRowSum()
{
    return rowSum;
}

const int * Table::getColSum()
{
    return colSum;
}

int Table::getGrandTotal()
{
    return 0;
}
