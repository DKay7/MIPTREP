#include "proc.h"
#include "stack.h"
#include <assert.h>
#include <math.h>

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int errno = 0;

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int AsmPush (Stack* stack, stack_type value)
{
    assert (stack);

    int stack_code = StackPush (stack, value);

    if (stack_code != STACK_OK)
    {
        errno = errno | PROC_INTERNAL_STACK_ERR;
        return errno;
    }

    errno = PROC_OK;
    return errno;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int AsmPop (Stack* stack, stack_type* value)
{
    assert (stack);

    if (stack->size < 1)
    {
        errno = errno | PROC_NOT_ENOUGH_VALUES_IN_STACK;
        return errno;
    }

    int stack_code = StackPop (stack, value);

    if (stack_code != STACK_OK)
    {
        errno = errno | PROC_INTERNAL_STACK_ERR;
        return errno;
    }
    
    errno = PROC_OK;
    return errno;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int AsmAdd (Stack* stack)
{
    assert (stack);

    if (stack->size < 2)
    {
        errno = errno | PROC_NOT_ENOUGH_VALUES_IN_STACK;
        return errno;
    }

    stack_type fisrt_term = STACK_DATA_POISON;
    stack_type second_term = STACK_DATA_POISON;

    int stack_code1 = StackPop (stack, &fisrt_term);
    int stack_code2 = StackPop (stack, &second_term);

    if (stack_code1 != STACK_OK || stack_code2 != STACK_OK)
    {
        errno = errno | PROC_INTERNAL_STACK_ERR;
        return errno;
    }

    StackPush (stack, fisrt_term + second_term);

    errno = PROC_OK;
    return errno;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int AsmSub (Stack* stack)
{
    assert (stack);

    if (stack->size < 2)
    {
        errno = errno | PROC_NOT_ENOUGH_VALUES_IN_STACK;
        return errno;
    }

    stack_type fisrt_term = STACK_DATA_POISON;
    stack_type second_term = STACK_DATA_POISON;

    int stack_code1 = StackPop (stack, &fisrt_term);
    int stack_code2 = StackPop (stack, &second_term);

    if (stack_code1 != STACK_OK || stack_code2 != STACK_OK)
    {
        errno = errno | PROC_INTERNAL_STACK_ERR;
        return errno;
    }

    StackPush (stack, fisrt_term - second_term);

    errno = PROC_OK;
    return errno;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int AsmMul (Stack* stack)
{
    assert (stack);

    if (stack->size < 2)
    {
        errno = errno | PROC_NOT_ENOUGH_VALUES_IN_STACK;
        return errno;
    }

    stack_type fisrt_term = STACK_DATA_POISON;
    stack_type second_term = STACK_DATA_POISON;

    int stack_code1 = StackPop (stack, &fisrt_term);
    int stack_code2 = StackPop (stack, &second_term);

    if (stack_code1 != STACK_OK || stack_code2 != STACK_OK)
    {
        errno = errno | PROC_INTERNAL_STACK_ERR;
        return errno;
    }

    StackPush (stack, fisrt_term * second_term);

    errno = PROC_OK;
    return errno;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int AsmDiv (Stack* stack)
{
    assert (stack);

    if (stack->size < 2)
    {
        errno = errno | PROC_NOT_ENOUGH_VALUES_IN_STACK;
        return errno;
    }

    stack_type fisrt_term = STACK_DATA_POISON;
    stack_type second_term = STACK_DATA_POISON;

    int stack_code1 = StackPop (stack, &fisrt_term);
    int stack_code2 = StackPop (stack, &second_term);

    if (stack_code1 != STACK_OK || stack_code2 != STACK_OK)
    {
        errno = errno | PROC_INTERNAL_STACK_ERR;
        return errno;
    }

    if (abs (second_term) < EPSILON)
    {
        errno = errno | PROC_ZERO_DIVISION_ERR;
        return errno;
    }

    StackPush (stack, fisrt_term / second_term);

    errno = PROC_OK;
    return errno;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
