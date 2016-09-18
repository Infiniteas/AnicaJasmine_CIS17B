#pragma once

#ifndef TABLE_H
#define TABLE_H

class Table {

	protected:
		int rows;
		int cols;
		int *rowSum;
		int *colSum;
		int *table;
		int grandTotal;
		void calcTable();
		Table();
		~Table();

	public:
		Table(int, int);
		const int *getTable();
		const int *getRowSum();
		const int *getColSum();
		int getGrandTotal();
};

#endif