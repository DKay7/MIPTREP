#include "list.h"
#include <stdio.h>

void DataPrinter (FILE* file, ll_type* data_to_print)
{   
    fprintf (file,
            R"(
                <td>mat:    %d</td>
                <td>kanava: %d</td>
            )",
            data_to_print->mat, data_to_print->kanava);
    return;
}

int main ()
{
    LinkedList list = {};
    data d1 { .mat = 0, .kanava = 1};
    data d2 { .mat = 1, .kanava = 2};
    data d3 { .mat = 2, .kanava = 3};

    LLCtor (&list, 10);

    int addr_d1 = LLInsertAfter(&list, 0, d1);

    LLInsertAfter(&list, 1, d2);
    LLInsertAfter(&list, 2, d3);

    LLDump(&list, DataPrinter);


    printf("%d\n", LLFindPhysicAdrres (&list, 1));
    printf("%d\n", LLFindPhysicAdrres (&list, 2));
    printf("%d\n", LLFindPhysicAdrres (&list, 3));

    LLDelete (&list, addr_d1);
    LLDump(&list, DataPrinter);

    printf("%d\n", LLFindPhysicAdrres (&list, 1));
    printf("%d\n", LLFindPhysicAdrres (&list, 2));
    printf("%d\n", LLFindPhysicAdrres (&list, 3));

    LLDump(&list, DataPrinter);
    printf("%d\n", LLFindPhysicAdrres (&list, 3));

    LLDtor (&list);

    return 0;
}