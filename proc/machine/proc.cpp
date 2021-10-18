#include "proc.h"
#include <assert.h>
#include <math.h>
#include <string.h>
//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int AsmPush (Stack* stack, stack_type value)
{
    int stack_code = StackPush (stack, value);

    if (stack_code != STACK_OK)
    {
        proc_errno = proc_errno | PROC_INTERNAL_STACK_ERR;
        return proc_errno;
    }

    proc_errno = PROC_OK;
    return proc_errno;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int AsmPop (Stack* stack, stack_type* value)
{
    if (stack->size < 1)
    {
        proc_errno = proc_errno | PROC_NOT_ENOUGH_VALUES_IN_STACK;
        return proc_errno;
    }

    int stack_code = StackPop (stack, value);

    if (stack_code != STACK_OK)
    {
        proc_errno = proc_errno | PROC_INTERNAL_STACK_ERR;
        return proc_errno;
    }
    
    proc_errno = PROC_OK;
    return proc_errno;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int AsmAdd (Stack* stack)
{
    if (stack->size < 2)
    {
        proc_errno = proc_errno | PROC_NOT_ENOUGH_VALUES_IN_STACK;
        return proc_errno;
    }

    stack_type fisrt_term = STACK_DATA_POISON;
    stack_type second_term = STACK_DATA_POISON;

    int stack_code1 = StackPop (stack, &fisrt_term);
    int stack_code2 = StackPop (stack, &second_term);

    if (stack_code1 != STACK_OK || stack_code2 != STACK_OK)
    {
        proc_errno = proc_errno | PROC_INTERNAL_STACK_ERR;
        return proc_errno;
    }

    StackPush (stack, fisrt_term + second_term);

    proc_errno = PROC_OK;
    return proc_errno;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int AsmSub (Stack* stack)
{
    if (stack->size < 2)
    {
        proc_errno = proc_errno | PROC_NOT_ENOUGH_VALUES_IN_STACK;
        return proc_errno;
    }

    stack_type fisrt_term = STACK_DATA_POISON;
    stack_type second_term = STACK_DATA_POISON;

    int stack_code1 = StackPop (stack, &fisrt_term);
    int stack_code2 = StackPop (stack, &second_term);

    if (stack_code1 != STACK_OK || stack_code2 != STACK_OK)
    {
        proc_errno = proc_errno | PROC_INTERNAL_STACK_ERR;
        return proc_errno;
    }

    StackPush (stack, fisrt_term - second_term);

    proc_errno = PROC_OK;
    return proc_errno;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int AsmMul (Stack* stack)
{
    if (stack->size < 2)
    {
        proc_errno = proc_errno | PROC_NOT_ENOUGH_VALUES_IN_STACK;
        return proc_errno;
    }

    stack_type fisrt_term = STACK_DATA_POISON;
    stack_type second_term = STACK_DATA_POISON;

    int stack_code1 = StackPop (stack, &fisrt_term);
    int stack_code2 = StackPop (stack, &second_term);

    if (stack_code1 != STACK_OK || stack_code2 != STACK_OK)
    {
        proc_errno = proc_errno | PROC_INTERNAL_STACK_ERR;
        return proc_errno;
    }

    StackPush (stack, fisrt_term * second_term);

    proc_errno = PROC_OK;
    return proc_errno;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int AsmDiv (Stack* stack)
{
    if (stack->size < 2)
    {
        proc_errno = proc_errno | PROC_NOT_ENOUGH_VALUES_IN_STACK;
        return proc_errno;
    }

    stack_type fisrt_term = STACK_DATA_POISON;
    stack_type second_term = STACK_DATA_POISON;

    int stack_code1 = StackPop (stack, &fisrt_term);
    int stack_code2 = StackPop (stack, &second_term);

    if (stack_code1 != STACK_OK || stack_code2 != STACK_OK)
    {
        proc_errno = proc_errno | PROC_INTERNAL_STACK_ERR;
        return proc_errno;
    }

    if (fabs (second_term) < EPSILON)
    {
        proc_errno = proc_errno | PROC_ZERO_DIVISION_ERR;
        return proc_errno;
    }

    StackPush (stack, fisrt_term / second_term);

    proc_errno = PROC_OK;
    return proc_errno;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int ProcDump (Stack* stack)
{
    printf ("ERROR NUM: %d\n", proc_errno);
    StackDump (stack);

    return proc_errno;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int ProcValidate (Stack* stack)
{
    StackValidate (stack, STACK_EXTERNAL_FUNC_CODE);

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

