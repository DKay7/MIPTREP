#include "proc.h"
#include <assert.h>
#include <math.h>
#include <string.h>

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int ProcProceesComand (Stack* stack, void* cmd_array, int *pc)
{   
    #define DEF_COMMAND (enum_name, n_arg, id, realization) \
    case id: \
        realization \
        break;

    switch (((unsigned char*) cmd_array)[*pc])
    {
    
    #include <commands.h>
    
    default:
        proc_errno |= PROC_UNKNOWN_CMD_ERR;
        return proc_errno;
    }

    return proc_errno;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void PrinterFunc (stack_type* el)
{
    printf ("%lf", *el);
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int ProcUnitTest()
{   
    Stack stack = {};
    StackCtor (&stack, 1);
    SetStackPrinterFunc (&stack, PrinterFunc);

    FILE* file = fopen ("asm_file.asm", "r");

    // AsmProcessFile (&stack, file);

    // ProcDump (&stack);

    StackDtor (&stack);


    return proc_errno;
}

