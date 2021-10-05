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
        stack->info.error_code = stack->info.error_code | STACK_MEM_ALLOCK_ERR;
        stack->info.error_func_code = stack->info.error_func_code | STACK_CTOR_CODE;

        return STACK_MEM_ALLOCK_ERR;
    }

    stack->start_bird = HUMMINGBIRD;
    stack->size = 0;
    stack->capacity = size;
    stack->data = tmp_pointer;
    stack->hash = StackHashSum (stack);
    stack->end_bird = HUMMINGBIRD;

    stack->info.print_function = NULL;
    stack->info.init_func = func_name;
    stack->info.stack_name = stack_name;
    stack->info.line = line;
    stack->info.filename = file_name;
    stack->info.error_code = STACK_OK;
    stack->info.error_func_code = 0;

    return StackValidate (stack, STACK_CTOR_CODE);
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int StackDtor (Stack* stack)
{   
    assert (stack);

    if (!stack->data)
    {   
        stack->info.error_code = stack->info.error_code | STACK_DTOR_DBL_CALL;
        stack->info.error_func_code = stack->info.error_func_code | STACK_DTOR_CODE;

        return STACK_DTOR_DBL_CALL;
    }

    memset (stack->data, STACK_DATA_POISON, stack->capacity);
    free (stack->data);

    return ValidateResult (stack, STACK_DTOR_CODE);
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
        stack->info.error_code = stack->info.error_code | err_code;
        stack->info.error_func_code = stack->info.error_func_code | STACK_PUSH_CODE;

        StackDump (stack);

        return err_code;
    }

    if (StackIncrease (stack) != STACK_OK)
    {   
        stack->info.error_code = stack->info.error_code | STACK_INCREASE_ERR;
        stack->info.error_func_code = stack->info.error_func_code | STACK_PUSH_CODE;

        return STACK_INCREASE_ERR;
    }

    stack->data[stack->size++] = element;
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
        stack->info.error_code = stack->info.error_code | err_code;
        stack->info.error_func_code = stack->info.error_func_code | STACK_POP_CODE;

        StackDump (stack);
        return err_code;
    }

    if (StackDecrease (stack) != STACK_OK)
    {   
        stack->info.error_code = stack->info.error_code | STACK_DECREASE_ERR;
        stack->info.error_func_code = stack->info.error_func_code | STACK_POP_CODE;

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
        stack_type* tmp = (stack_type*) realloc (stack->data, 2 * stack->capacity);

        if (!tmp)
        {
            stack->info.error_code = stack->info.error_code | STACK_MEM_ALLOCK_ERR;
            stack->info.error_func_code = stack->info.error_func_code | STACK_INCREASE_CODE;

            return STACK_MEM_ALLOCK_ERR;
        }

        stack->data = tmp;
        stack->capacity = 2 * stack->capacity;
    }
    
    return ValidateResult (stack, STACK_INCREASE_CODE);
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int StackDecrease (Stack* stack)
{
    assert (stack);
    assert (stack->data);

    if (stack->size < stack->capacity / 2)
    {
        stack_type* tmp = (stack_type*) realloc (stack->data, stack->capacity / 2 + 1);

        if (!tmp)
        {   
            stack->info.error_code = stack->info.error_code | STACK_MEM_ALLOCK_ERR;
            stack->info.error_func_code = stack->info.error_func_code | STACK_DECREASE_CODE;

            return STACK_MEM_ALLOCK_ERR;
        }

        stack->data = tmp;
        stack->capacity = stack->capacity / 2 + 1;
    }

    return ValidateResult (stack, STACK_DECREASE_CODE);
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int StackValidate (Stack* stack, int func_code)
{
    assert (stack);

    if(stack->data == NULL)
    {
        stack->info.error_code = stack->info.error_code | STACK_INCORRECT_DATA_PTR;
    }

    if(stack->start_bird != HUMMINGBIRD)
    {
        stack->info.error_code = stack->info.error_code | STACK_WRONG_START_HUMMINGBIRD;
    }

    if(stack->start_bird != HUMMINGBIRD)
    {
        stack->info.error_code = stack->info.error_code |  STACK_WRONG_END_HUMMINGBIRD;
    }

    if(stack->size > stack->capacity)
    {
        stack->info.error_code = stack->info.error_code |  STACK_INCORRECT_SIZE;
    }

    if(stack->hash != StackHashSum (stack))
    {
        stack->info.error_code = stack->info.error_code |  STACK_WRONG_HASH_SUM;
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

    printf ("[%p] ", &stack->data);
    printf ("\"%s\" was init. in func. %s line %d file %s \n", stack->info.stack_name, stack->info.init_func, stack->info.line, stack->info.filename);
    printf ("Dump for \"%s\" called in func. %s, line %d, file %s'\n", stack_name, func_name, line, file_name);
 
    if(err_code != STACK_OK)
    {
        StackPrintExitCode(stack);
    }

    printf ("\n{\n");              
                                                
    printf (" size = %lu \n", stack->size);           
                                                    
    printf (" capacity = %lu\n", stack->capacity);    
                                                    
    printf (" hash_sum = %llX\n", stack->hash);       
                                                    
    printf ("\t{\n"); 

    for (size_t i = 0; i < stack->capacity; i++)
    {
        printf ("   ");      

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

            for (size_t j = 0; j <  sizeof (stack_type); j++)
            {
                printf ("%02X ", data_ptr[j]);
            }
        }

        printf  ("\n");
    }

    printf ("   }\n}\n");

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

    if (err_code & STACK_MEM_ALLOCK_ERR)
    {
        printf (RED_COLOR("Memory allocation error\n"));
        err_code -= STACK_MEM_ALLOCK_ERR;
    }

    if (err_code & STACK_INCORRECT_DATA_PTR)
    {
        printf (RED_COLOR("Incorrect pointer to start of buffer founded\n"));
        err_code -= STACK_INCORRECT_DATA_PTR;
    }

    if (err_code & STACK_WRONG_START_HUMMINGBIRD)
    {
        printf (RED_COLOR("Changes in start hummingbird founded\n"));
        err_code -= STACK_WRONG_START_HUMMINGBIRD;
    }

    if (err_code & STACK_WRONG_END_HUMMINGBIRD)
    {
        printf (RED_COLOR("Changes in end hummingbird founded\n")); 
        err_code -= STACK_WRONG_END_HUMMINGBIRD;
    }

    if (err_code & STACK_WRONG_HASH_SUM)
    {
        printf (RED_COLOR("Mismacth of hash sum founded\n"));
        err_code -= STACK_WRONG_HASH_SUM;
    }

    if (err_code & STACK_CTOR_DBL_CALL)
    {
        printf (RED_COLOR("Stack constructor was called twice\n"));
        err_code -= STACK_CTOR_DBL_CALL;
    }

    if (err_code & STACK_DTOR_DBL_CALL)
    {
        printf (RED_COLOR("Stack destructor was called twice\n"));
        err_code -= STACK_DTOR_DBL_CALL;
    }

    if (err_code & STACK_INCORRECT_CAPACITY)
    {
        printf (RED_COLOR("Stack capcity is incorrect\n"));
        err_code -= STACK_INCORRECT_CAPACITY;
    }

    if (err_code & STACK_INCORRECT_SIZE)
    {
        printf (RED_COLOR("Stack size is incorrect\n"));
        err_code -= STACK_INCORRECT_SIZE;
    }

    if (err_code & STACK_INCREASE_ERR)
    {
        printf (RED_COLOR("Error while increasing stack\n"));
        err_code -= STACK_INCREASE_ERR;
    }

    if (err_code & STACK_DECREASE_ERR)
    {
        printf (RED_COLOR("Error while decreasing stack\n"));
        err_code -= STACK_DECREASE_ERR;
    }

    if (err_code != 0)
    {
        printf (RED_COLOR("Unkwonw exception with code %X \n"), err_code);
    }

    printf ("\nErrors were reached in next function(s): \n");

    if (func_code & STACK_CTOR_CODE)
    {
        printf (RED_COLOR("StackCtor()\n"));
        func_code -= STACK_CTOR_CODE;
    }

    if (func_code & STACK_DTOR_CODE)
    {
        printf (RED_COLOR("StackDtor()\n"));
        func_code -= STACK_DTOR_CODE;
    }

    if (func_code & STACK_PUSH_CODE)
    {
        printf (RED_COLOR("StackPush()\n"));
        func_code -= STACK_PUSH_CODE;
    }

    if (func_code & STACK_POP_CODE)
    {
        printf (RED_COLOR("StackPop()\n"));
        func_code -= STACK_POP_CODE;
    }

    if (func_code & STACK_INCREASE_CODE)
    {
        printf (RED_COLOR("StackIncrease()\n"));
        func_code -= STACK_INCREASE_CODE;
    }

    if (func_code & STACK_DECREASE_CODE)
    {
        printf (RED_COLOR("StackDecrease()\n"));
        func_code -= STACK_DECREASE_CODE;
    }

    if (func_code & STACK_DUMP_CODE)
    {
        printf (RED_COLOR("StackDump()\n"));
        func_code -= STACK_DUMP_CODE;
    }

    if (func_code & STACK_UNIT_TEST_CODE)
    {
        printf (RED_COLOR("UnitTest()\n"));
        func_code -= STACK_UNIT_TEST_CODE;
    }

    if (func_code & STACK_SET_PRINTER_CODE)
    {
        printf (RED_COLOR("SetStackPrinter()\n"));
        func_code -= STACK_SET_PRINTER_CODE;
    }

    if (func_code & STACK_PRINT_EXIT_CODE_CODE)
    {
        printf (RED_COLOR("PrintExitCode()\n"));
        func_code -= STACK_PRINT_EXIT_CODE_CODE;
    }

    if (func_code & STACK_VALIDATE_CODE)
    {
        printf (RED_COLOR("StackValidate()\n"));
        func_code -= STACK_VALIDATE_CODE;
    }

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

    char* ptr = (char*) pointer;

    for (unsigned i = 0; i < size; i++)
    {
        hash += *(ptr + i);
        hash = hash << i;
    }

    return hash;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

unsigned long long StackHashSum(Stack* stack)
{
    assert(stack);
    unsigned long long old_hash = stack->hash;
    stack->hash = 0;
    unsigned long long hash = HashSum (stack, sizeof(stack));

    #ifdef DATA_HASHING
    hash = HashSum (stack->data, stack->size * sizeof (stack_type), hash);
    #endif
    
    stack->hash = old_hash;
    return hash;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void stack_hex_printer (stack_type* data)
{
    printf ("%X", *data);
}

int UnitTest ()
{   
    Stack stack1 = {};
    StackCtor (&stack1, 10);
    StackDump (&stack1);

    StackPush(&stack1, 256);
    StackPush(&stack1, 8);
    StackPush(&stack1, 9);
    StackPush(&stack1, 0xFFFFFFAF);
    StackDump (&stack1);

    int el = 666;
    StackPop (&stack1, &el);
    SetStackPrinterFunc (&stack1, stack_hex_printer);

    stack1.info.error_code = 0x000001C3;
    stack1.info.error_func_code = 0x000004C3;
    StackDump (&stack1);

    StackDtor (&stack1);

    return 0;
}
