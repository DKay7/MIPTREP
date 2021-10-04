#include "stack.h"
#include <malloc.h>
#include <assert.h>
#include <string.h>

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
int StackCtorFunc (Stack* stack, size_t size, const char* stack_name, const char* func_name, int line, const char* file_name)
{   
    assert (stack);
    assert (size);
    
    if (stack->data != NULL)
    {
        return STACK_CTOR_DBL_CALL;
    }

    stack_type* tmp_pointer = (stack_type*) calloc (size, sizeof (stack_type));

    if (!tmp_pointer)
    {   
        stack->error_code = STACK_CTOR_CODE + STACK_MEM_ALLOCK_ERR;
        return STACK_MEM_ALLOCK_ERR;
    }

    stack->start_bird = HUMMINGBIRD;
    stack->data = tmp_pointer;
    stack->init_func = func_name;
    stack->stack_name = stack_name;
    stack->line = line;
    stack->filename = file_name;
    stack->size = 0;
    stack->capacity = size;
    stack->end_bird = HUMMINGBIRD;
    stack->hash = StackHashSum (stack);

    return STACK_OK;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int StackDtor (Stack* stack)
{   
    assert (stack);

    if (!stack->data)
    {
        return STACK_DTOR_DBL_CALL;
    }

    memset (stack->data, STACK_DATA_POISON, stack->capacity);
    free (stack->data);

    return STACK_OK;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int SetStackPrinterFunc (Stack* stack, void (*printer_func)(stack_type*))
{
    stack->print_function = printer_func;
    return STACK_OK;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int StackPush (Stack* stack, stack_type element)
{
    assert (stack);
    int err_code = 0;

    if ((err_code = StackValidate (stack, STACK_PUSH_CODE)) != STACK_OK)
    {
        StackDump (stack);
        return err_code;
    }

    if (StackIncrease (stack) != STACK_OK)
    {
        return STACK_INCREASE_ERR;
    }

    stack->data[stack->size++] = element;
    stack->hash = StackHashSum (stack);

    return STACK_OK;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int StackPop (Stack* stack, stack_type* out_element)
{
    assert (stack);
    
    int err_code = 0;

    if ((err_code = StackValidate (stack, STACK_POP_CODE)) != STACK_OK)
    {
        StackDump (stack);
        return err_code;
    }

    if (StackDecrease (stack) != STACK_OK)
    {
        return STACK_DECREASE_ERR;
    }

    *out_element = stack->data[--stack->size];
    stack->data[stack->size] = STACK_DATA_POISON; //TODO чем заполнить??
    stack->hash = StackHashSum (stack);

    return STACK_OK;
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
            stack->error_code = STACK_MEM_ALLOCK_ERR + STACK_INCREASE_CODE;

            return STACK_MEM_ALLOCK_ERR;
        }

        stack->data = tmp;
        stack->capacity = 2 * stack->capacity;
    }

    return STACK_OK;
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
            stack->error_code = STACK_MEM_ALLOCK_ERR + STACK_INCREASE_CODE;

            return STACK_MEM_ALLOCK_ERR;
        }

        stack->data = tmp;
        stack->capacity = stack->capacity / 2 + 1;
    }

    return STACK_OK;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int StackValidate (Stack* stack, int func_code)
{
    assert (stack);

     if(stack->data == NULL)
    {
        stack->error_code = STACK_INCORRECT_DATA_PTR + func_code;
    }

    if(stack->start_bird != HUMMINGBIRD)
    {
        stack->error_code = STACK_WRONG_START_HUMMINGBIRD + func_code;
    }

    if(stack->start_bird != HUMMINGBIRD)
    {
        stack->error_code = STACK_WRONG_END_HUMMINGBIRD + func_code;
    }

    if(stack->size > stack->capacity)
    {
        stack->error_code = STACK_INCORRECT_SIZE + func_code;
    }

    if(stack->hash != StackHashSum(stack))
    {
        stack->error_code = STACK_WRONG_HASH_SUM + func_code;
    }

    return stack->error_code;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int StackDumpFunc (Stack* stack, const int line, const char* func_name, const char* file_name, const char* stack_name)
{
    int err_and_func_code = StackValidate (stack, STACK_DUMP_CODE);
    int err_code = err_and_func_code % 256;

    printf ("STACK \"%s\" was init. in func. %s line %d file %s \n", 
            stack->stack_name, stack->init_func, stack->line, stack->filename);

    if (err_code == STACK_OK)
    {
        printf (GREEN_COLOR("[OK]: "));
    }
    
    else
    {
        printf (RED_COLOR("[ERROR][CODE: 0x%X]"), err_code);
    }

    printf ("[%p] ", &stack->data);

    printf ("Dump for %s called in func. %s, line %d, file %s'\n", stack_name, func_name, line, file_name);
 
    if(err_code != STACK_OK)
    {   
        StackPrintExitCode(err_and_func_code);
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

        if (stack->print_function)
        {
            stack->print_function (stack->data + i);
        }
        else
        {   
            //TODO перепроверить побитовую печать
            char* data_ptr = (char*) (stack->data + i);

            for (size_t j = 0; j < sizeof (stack_type); j++)
            {
                printf ("%02X ", data_ptr[j]);
            }
        }

        printf  ("\n");
    }

    printf ("   }\n}\n");

    return STACK_OK;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int StackPrintExitCode(int err_and_func_code)
{   
    int err_code = err_and_func_code % 256;
    int func_code = err_and_func_code / 256;
    
    if (err_code == STACK_OK)
    {
        printf ("No errors founded\n");
        return 0;
    }

    switch (err_code)
    {
        case STACK_MEM_ALLOCK_ERR:
            printf ("Memory allocation error in ");
            break;
    
        case STACK_INCORRECT_DATA_PTR:
            printf ("Incorrect pointer to start of buffer founded in ");
            break;

        case STACK_INCORRECT_SIZE:
            printf ("Stack size below zero or stack overdlow exception founded in ");
            break;

        case STACK_INCORRECT_CAPACITY:
            printf ("Stack capacity below zeor  founded in ");
            break;

        case STACK_WRONG_START_HUMMINGBIRD:
            printf ("Changes in start hummingbird founded in ");
            break;

        case STACK_WRONG_END_HUMMINGBIRD:
            printf ("Changes in end hummingbird founded in ");
            break;

        case STACK_WRONG_HASH_SUM:
            printf ("Mismacth of hash sum founded in ");
            break;

        default:
            printf ("Unkwonw exception with number %X in ", err_code);
            break;
    }

    switch (func_code)
    {
        case STACK_CTOR_CODE:
            printf ("func StackCtor()\n");
            break;

        case STACK_PUSH_CODE:
            printf ("func StackPush()\n");
            break;

        case STACK_POP_CODE:
            printf ("func StackPop()\n");
            break;

        case STACK_INCREASE_CODE:
            printf ("func StackIncrease()\n");
            break;

        case STACK_DECREASE_CODE:
            printf ("func StackDecrease()\n");
            break;

        case STACK_DUMP_CODE:
            printf ("macro StackDump()\n");
            break;

        default:
            printf ("unkwonw func with number %X\n", func_code);
            break;
    }

    return 0;
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

    size_t first_part_size =  sizeof (Stack) - sizeof (hummingbird_type) - sizeof (unsigned long long);

    unsigned long long struct_hash_1st_part = HashSum (stack, first_part_size);
    unsigned long long hash = HashSum (&stack->end_bird, sizeof(hummingbird_type), struct_hash_1st_part);

    #ifdef DATA_HASHING
    hash = HashSum (stack->data, stack->size * sizeof (stack_type), hash);
    #endif

    return hash;
}

void stack_hex_printer (stack_type* data)
{
    printf ("%X", *data);
}

int UnitTest ()
{
    Stack stack1 = {};
    StackCtor (&stack1, 10);
    SetStackPrinterFunc (&stack1, stack_hex_printer);

    StackDump (&stack1);
    StackPush(&stack1, 7);
    StackPush(&stack1, 8);
    StackPush(&stack1, 9);
    StackPush(&stack1, 16384);
    StackDump (&stack1);

    int el = 666;
    StackPop (&stack1, &el);
    StackDump (&stack1);

    printf ("\n%d\n", el);
    StackDtor (&stack1);

    return 0;
}
