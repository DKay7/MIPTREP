// This is unit-test file!

#include "list.h"
#include <stdio.h>

struct data
{
    int mat = -1;
    int kanava = -1;
    int one_filed = 100;
};


//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void DataPrinter (FILE* file, data* data_to_print)
{   
    fprintf (file,
            R"( 
                <table border="0" cellborder="1" cellspacing="0">
                <tr>
                <td>mat:    %d</td>
                </tr>
                <tr>
                <td>kanava: %d</td>
                </tr>
                <tr>
                <td>another: %d</td>
                </tr>
                </table>
            )",
            data_to_print->mat, data_to_print->kanava, data_to_print->one_filed);

    return;
}

int main ()
{   
    LinkedList<data> list = {};
    data d1 = { .mat = 7, .kanava = 8};
    data d2 = { .mat = 1, .kanava = 2};
    data d3 = { .mat = 2, .kanava = 3};
    data d4 = { .mat = 12, .kanava = 13};

    LLCtor (&list, 10);

    int addr_d1 = LLInsertAfter(&list, 0, d1);
    int addr_d2 = LLInsertAfter(&list, 1, d2);
    int addr_d3 = LLInsertAfter(&list, 2, d3);

    LLDump(&list, DataPrinter);


    printf("%d\n", LLFindPhysicAdrres (&list, 1));
    printf("%d\n", LLFindPhysicAdrres (&list, 2));
    printf("%d\n", LLFindPhysicAdrres (&list, 3));

    LLDelete (&list, addr_d1);
    LLDelete (&list, addr_d2);
    LLDump(&list, DataPrinter);

    LLInsertAfter (&list, addr_d3, d4);
    LLDelete (&list, addr_d3);
    LLDump(&list, DataPrinter);

    printf("%d\n", LLFindPhysicAdrres (&list, 1));
    printf("%d\n", LLFindPhysicAdrres (&list, 2));
    printf("%d\n", LLFindPhysicAdrres (&list, 3));

    LLDump(&list, DataPrinter);
    printf("%d\n", LLFindPhysicAdrres (&list, 3));

    LLDtor (&list);

    return 0;
}