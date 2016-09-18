#include "Table.h"
#include "TableInherited.h"
#include <iostream>
using namespace std;

TableInherited::TableInherited(int r, int c)
{
	rows = r;
	cols = c;

	//calls the protected function from the base class
	Table::calcTable();

	//declares the size of the augTable
	augTable = new int[(rows + 1)*(cols + 1)];

	//initializes all values in the augTable to 0
	for (int i = 0; i < (rows + 1)*(cols + 1); i++) {
		augTable[i] = 0;
	}

	//calls the function to calculate the new table
	calcAugTable();


}


void TableInherited::calcAugTable()
{
	int rowSumCounter = 0;

	//points to the table to manipulate it
	const int *tempTable = getTable();

	//this will be the index for the original table
	int tempTableIndex = 0;

	//for loop to input the original values plus the sums
	//of the columns and rows
	for (int i = 0; i < rows*(cols + 1); i++)
	{
		if (tempTableIndex < rows*cols) {

			//adds the original values to the new table
			augTable[i] = tempTable[tempTableIndex];

			//an index to iterate through the original table in each loop
			tempTableIndex++;
		}
		
		
		//adds the sum row at the end of each row
		if (i % (cols+1) == rows) 
		{
			i++;
			augTable[i] = rowSum[rowSumCounter];
			//an index to iterate through the rowSum array
			rowSumCounter++;
		}

		//if statement to add the colSum array to the end of
		//of the table
		if (i == (rows*(cols + 1)) - 1) 
		{
			i++;
			for (int j = 0; j < cols; j++) 
			{
				//input the colSum into the table
				augTable[i+j] = colSum[j];
			}

			//add the grandtotal tot he last element of the augTable array
			augTable[((rows + 1)*(cols + 1))-1] = grandTotal;
		}
	}
}
TableInherited::~TableInherited()
{
	delete[] augTable;
}

const int * TableInherited::getAugTable()
{
	return augTable;
}
