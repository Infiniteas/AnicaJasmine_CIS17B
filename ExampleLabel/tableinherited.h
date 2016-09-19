#ifndef TABLEINHERITED_H
#define TABLEINHERITED_H

#include "Table.h"

class TableInherited :public Table {

    protected:
        int *augTable;
        void calcAugTable();
    public:
        TableInherited(int, int);        //Constructor
        ~TableInherited();				//Destructor
        const int *getAugTable();
};


#endif // TABLEINHERITED_H
