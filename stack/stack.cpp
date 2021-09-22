#include <stack.h>
#include <malloc.h>
#include <assert.h>
#include <string.h>

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int StackCtor (Stack* stack, size_t size)
{   
    assert (stack);
    assert (size);

    stack_type* tmp_pointer = (stack_type*) calloc (size, sizeof (stack_type));

    if (!tmp_pointer)
    {   
        stack->error_code = STACK_CTOR + STACK_MEM_ALLOCK_ERR;
        return STACK_MEM_ALLOCK_ERR;
    }

    stack->data = tmp_pointer;
    stack->size = 0;
    stack->capacity = size;
    
    return STACK_OK;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int StackDtor (Stack* stack)
{   
    assert (stack);

    memset (stack->data, STACK_DATA_POISON, stack->capacity);
    free (stack->data);
    free (stack);

    return STACK_OK;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int StackPush (Stack* stack, stack_type element)
{
    assert (stack);
    
    if (!StackIncrease (stack))
    {
        return STACK_INCREASE_ERR;
    }

    stack->data [stack->size++] = element;

    return STACK_OK;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int StackPop (Stack* stack, stack_type* out_element)
{
        assert (stack);
    
    if (!StackDecrease (stack))
    {
        return STACK_DECREASE_ERR;
    }

    *out_element = stack->data [--stack->size];

    return STACK_OK;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int StackDumpFunction (Stack* stack, int line, char* func_name, char* file_name,  char* stack_name)
{   
    assert (stack);

    // TODO finish it
    return stack->error_code;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int StackValidateFunc (Stack* stack)
{
    assert (stack);

    // TODO finish it

    return STACK_OK;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int StackIncrease (Stack* stack)
{
    assert (stack);
    assert (stack->data);

    if (stack->size > (3/4)*stack->capacity)
    {
        stack_type* tmp = (stack_type*) realloc (stack->data, 2 * stack->size);

        if (!tmp)
        {
            stack->error_code = STACK_MEM_ALLOCK_ERR + STACK_INCREASE_ERR;

            return STACK_MEM_ALLOCK_ERR;
        }
    }

    
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int StackDecrease (Stack* stack)
{

}