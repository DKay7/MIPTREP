#include "stack.h"
#include <malloc.h>
#include <assert.h>
#include <string.h>

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int StackCtorFunc (Stack* stack, size_t size, const char* stack_name, const char* func_name, int line, const char* file_name)
{   
    assert (stack);
    assert (size);
    assert (func_name);
    assert (file_name);
    assert (stack_name);

    if (stack->data != NULL)
    {
        return STACK_CTOR_DBL_CALL;
    }

    stack_type* tmp_pointer = (stack_type*) calloc (size, sizeof (stack_type));

    if (!tmp_pointer)
    {   
        stack->info.error_code |= STACK_MEM_ALLOCK_ERR;
        stack->info.error_func_code |=  STACK_CTOR_CODE;
        return STACK_MEM_ALLOCK_ERR;
    }

    stack->start_bird = HUMMINGBIRD;
    stack->size = 0;
    stack->capacity = size;
    stack->data = tmp_pointer;

    StackPoison (stack, 0, stack->capacity);

    stack->end_bird = HUMMINGBIRD;

    stack->info.print_function = NULL;
    stack->info.init_func = func_name;
    stack->info.stack_name = stack_name;
    stack->info.line = line;
    stack->info.filename = file_name;
    stack->info.error_code = STACK_OK;
    stack->info.error_func_code = 0;

    stack->hash = StackHashSum (stack);

    return StackValidate (stack, STACK_CTOR_CODE);
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int StackDtor (Stack* stack)
{   
    assert (stack);

    if (!stack->data)
    {   
        stack->info.error_code |= STACK_DTOR_DBL_CALL;
        stack->info.error_func_code |= STACK_DTOR_CODE;

        return STACK_DTOR_DBL_CALL;
    }

    StackPoison (stack, 0, stack->capacity);

    stack->capacity = 0;
    stack->size = 0;
    stack->hash = 0;
    stack->info.error_code = STACK_NOT_CREATED;
    stack->info.error_func_code = STACK_DTOR_CODE;
    stack->info.stack_name = NULL;
    stack->info.init_func = NULL;
    stack->info.filename = NULL;
    stack->info.line = -1;
    stack->info.print_function = NULL;
    stack->info.stack_name = NULL;

    free (stack->data);
    stack->data = NULL;

    return ValidateResult (stack, STACK_DTOR_CODE);
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void StackPoison (Stack* stack, size_t start, size_t num)
{   
    assert (stack);
    assert (num <= stack->capacity);

    for (size_t i = start; i < num; i++)
    {
        stack->data[i] = STACK_DATA_POISON;
    }

    return;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int SetStackPrinterFunc (Stack* stack, void (*printer_func)(stack_type*))
{   
    assert (stack);
    assert (printer_func);

    stack->info.print_function = printer_func;
    stack->hash = StackHashSum (stack);

    return ValidateResult (stack, SET_STACK_PRINTER_CODE);

}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int StackPush (Stack* stack, stack_type element)
{
    assert (stack);
    assert(stack->data);

    int err_code = 0;

    if ((err_code = StackValidate (stack, STACK_PUSH_CODE)) != STACK_OK)
    {   
        StackDump (stack);
        return err_code;
    }

    if (StackIncrease (stack) != STACK_OK)
    {   
        stack->info.error_code |= STACK_INCREASE_ERR;
        stack->info.error_func_code |= STACK_PUSH_CODE;

        return STACK_INCREASE_ERR;
    }

    stack->data[stack->size] = element;
    stack->size++;
    stack->hash = StackHashSum (stack);

    return ValidateResult (stack, STACK_PUSH_CODE);
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int StackPop (Stack* stack, stack_type* out_element)
{
    assert (stack);
    assert (out_element);

    int err_code = 0;

    if ((err_code = StackValidate (stack, STACK_POP_CODE)) != STACK_OK)
    {   
        stack->info.error_code |= err_code;
        stack->info.error_func_code |= STACK_POP_CODE;

        StackDump (stack);
        return err_code;
    }

    if (StackDecrease (stack) != STACK_OK)
    {   
        stack->info.error_code |= STACK_DECREASE_ERR;
        stack->info.error_func_code |= STACK_POP_CODE;

        return STACK_DECREASE_ERR;
    }

    *out_element = stack->data[--stack->size];
    stack->data[stack->size] = STACK_DATA_POISON;
    stack->hash = StackHashSum (stack);

    return ValidateResult (stack, STACK_POP_CODE);
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int StackIncrease (Stack* stack)
{
    assert (stack);
    assert (stack->data);

    if (stack->size + 1 > stack->capacity)
    {
        stack_type* tmp = (stack_type*) realloc (stack->data, (int)((STACK_INCREASE_COEFFICIENT) * stack->capacity + 1) * sizeof (stack_type));

        if (!tmp)
        {
            stack->info.error_code |= STACK_MEM_ALLOCK_ERR;
            stack->info.error_func_code |= STACK_INCREASE_CODE;

            return STACK_MEM_ALLOCK_ERR;
        }

        stack->data = tmp;
        stack->capacity = (int)((STACK_INCREASE_COEFFICIENT) * stack->capacity + 1);

        StackPoison (stack, stack->size + 1, stack->capacity);
        stack->hash = StackHashSum (stack);
    }
    
    return ValidateResult (stack, STACK_INCREASE_CODE);
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int StackDecrease (Stack* stack)
{
    assert (stack);
    assert (stack->data);

    if (stack->size < (STACK_DECREASE_COEFFICIENT) * stack->capacity)
    {
        stack_type* tmp = (stack_type*) realloc (stack->data, (int)((STACK_DECREASE_COEFFICIENT) * stack->capacity + 1) * sizeof (stack_type));

        if (!tmp)
        {   
            stack->info.error_code |= STACK_MEM_ALLOCK_ERR;
            stack->info.error_func_code |= STACK_DECREASE_CODE;

            return STACK_MEM_ALLOCK_ERR;
        }

        stack->data = tmp;
        stack->capacity = (int)((STACK_DECREASE_COEFFICIENT) * stack->capacity + 1);
        stack->hash = StackHashSum (stack);
    }

    return ValidateResult (stack, STACK_DECREASE_CODE);
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int StackValidate (Stack* stack, int func_code)
{
    assert (stack);

    if(stack->data == NULL)
    {
        stack->info.error_code |= STACK_INCORRECT_DATA_PTR;
    }

    if(stack->start_bird != HUMMINGBIRD)
    {
        stack->info.error_code |= STACK_WRONG_START_HUMMINGBIRD;
    }

    if(stack->end_bird != HUMMINGBIRD)
    {
        stack->info.error_code |= STACK_WRONG_END_HUMMINGBIRD;
    }

    if(stack->size > stack->capacity)
    {
        stack->info.error_code |= STACK_INCORRECT_SIZE;
    }

    if(stack->hash != StackHashSum (stack))
    {   
        stack->info.error_code |= STACK_WRONG_HASH_SUM;
    }

    stack->info.error_func_code = stack->info.error_func_code |  STACK_VALIDATE_CODE;
    stack->info.error_func_code   = stack->info.error_func_code |  func_code;

    return stack->info.error_code;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int StackDumpFunc (Stack* stack, const int line, const char* func_name, const char* file_name, const char* stack_name)
{   
    assert (stack);
    assert (func_name);
    assert (file_name);
    assert (stack_name);

    int err_code = StackValidate (stack, STACK_DUMP_CODE);

    if (err_code == STACK_OK)
    {
        printf (GREEN_COLOR("\nSTACK [OK]: "));
    }
    
    else
    {
        printf (RED_COLOR("\nSTACK [ERROR][ERR_CODE: 0x%X]"), err_code);
    }

    printf ("[%p] \"%s\" was init. in func. %s line %d file %s \n"
            "Dump for \"%s\" called in func. %s, line %d, file %s'\n", &stack->data, stack->info.stack_name, stack->info.init_func, stack->info.line, stack->info.filename, stack_name, func_name, line, file_name);
 
    if(err_code != STACK_OK)
    {
        StackPrintExitCode(stack);
    }

    printf ("\n{\n"
            " size = %lu \n"    
            " capacity = %lu\n"
            " hash_sum = %llX\n"
            "\t{\n", stack->size, stack->capacity, stack->hash); 

    for (size_t i = 0; i < stack->capacity; i++)
    {
        printf ("\t");      

        if (i < stack->size)
        {                      
           printf  ("\t *");
        }
        else
        {                    
            printf ("\t  ");
        }

        printf  ("[%lu] = ", i);

        if (stack->info.print_function)
        {
            stack->info.print_function (stack->data + i);
        }
        else
        {   
            unsigned char* data_ptr = (unsigned char*) (stack->data + i);

            for (size_t j = 0; j < sizeof (stack_type); j++)
            {
                printf ("%02X ", data_ptr[j]);
            }
        }

        printf  ("\n");
    }

    printf ("\t}\n}\n");

    return ValidateResult (stack, STACK_DUMP_CODE);
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int StackPrintExitCode(Stack* stack)
{   
    if (stack->info.error_code == STACK_OK)
    {
        printf (GREEN_COLOR("No errors founded\n"));
        return ValidateResult (stack, STACK_PRINT_EXIT_CODE_CODE);
    } 

    int err_code = stack->info.error_code;
    int func_code = stack->info.error_func_code;
    printf ("\nThere are some errors in stack: \n");

    #include "defines/print_err_code_define.h"

    if (err_code != 0)
    {
        printf (RED_COLOR("Unkwonw exception with code %X \n"), err_code);
    }

    printf ("\nErrors were reached in next function(s): \n");

    #include "defines/print_func_code_define.h"
    
    if (func_code != 0)
    {
        printf (RED_COLOR("Unkwonw function with code: %X\n"), func_code);
    }

    printf ("\n");

    return ValidateResult (stack, STACK_PRINT_EXIT_CODE_CODE);
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

unsigned long long HashSum(void* pointer, size_t size, unsigned long long hash)
{
    assert(pointer);

    unsigned char* ptr = (unsigned char*) pointer;

    for (size_t i = 0; i < size; i++)
    {
        hash += *(ptr + i);
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }

    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);

    return hash;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

unsigned long long StackHashSum(Stack* stack)
{
    assert(stack);

    unsigned long long old_hash = stack->hash;
    int stack_err_code = stack->info.error_code;
    int stack_err_func_code = stack->info.error_func_code;

    stack->info.error_code = 0;
    stack->info.error_func_code = 0;
    stack->hash = 0;

    unsigned long long hash = HashSum (stack, sizeof(*stack));

    #ifdef DATA_HASHING
    hash = HashSum (stack->data, stack->size * sizeof (stack_type), hash);
    #endif
    
    stack->info.error_code = stack_err_code;
    stack->info.error_func_code = stack_err_func_code;
    stack->hash = old_hash;
    
    return hash;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int UnitTest ()
{   
    Stack stack1 = {};

    StackCtor (&stack1, 1);
    StackDump(&stack1);
    
    printf ("%llX\n", stack1.hash);
    printf ("%llX\n", StackHashSum (&stack1));

    StackPush(&stack1, 3078);
    StackPush(&stack1, 255);
    StackPush(&stack1, 3565);
    StackDump(&stack1);

    // stack1.capacity = 15;
    StackDump(&stack1);
    StackDtor (&stack1);

    return 0;
}
