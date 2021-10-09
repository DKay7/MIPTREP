#include "proc.h"

#include <assert.h>
#include <math.h>
#include <string.h>

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int errno = PROC_OK;

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

int AsmParseCommand(Stack* stack, String* command_and_args)
{   
    assert (command_and_args);
    assert (stack);

    char* command_name = NULL;
    int num_cmds = sscanf (command_and_args->start, "%ms", &command_name);

    if (num_cmds <= 0)
    {
        errno = errno | PROC_ERR_READING_CMD_NAME;
        return errno;
    }

    if (strcmp (command_name, "pop") == 0)
    {   
        // POP CASE
        stack_type arg = STACK_DATA_POISON;
        errno = AsmPop (stack, &arg);
    }

    else if (strcmp (command_name, "push") == 0)
    {
        // PUSH case;
        stack_type arg = STACK_DATA_POISON;
        int num_readed_symbols = sscanf (command_and_args->start, "push " STACK_TYPE_SPEC, &arg);
        CHECK_ARGS_NUM (num_readed_symbols, 1);
        errno = AsmPush (stack, arg);
    }

    else if (strcmp (command_name, "add") == 0)
    {
        // ADD case;
        errno = AsmAdd (stack);
    }

    else if (strcmp (command_name, "sub") == 0)
    {
        // SUB case;
        errno = AsmSub (stack);
    }

    else if (strcmp (command_name, "mul") == 0)
    {
        // MUL case;
        errno = AsmMul (stack);
    }

    else if (strcmp (command_name, "div") == 0)
    {
        // DIV case;
        errno = AsmDiv (stack);
    }

    else if (strcmp (command_name, "dump") == 0)
    {
        // DUNP case;
        errno = ProcDump (stack);
    }

    else if (strcmp (command_name, "validate") == 0)
    {
        // DUNP case;
        errno = ProcValidate (stack);
    }

    else
    {
        errno = errno | PROC_ERR_READING_CMD_NAME;
    }


    if (errno != PROC_OK)
    {
        ProcDump(stack);
    }

    free (command_name);

    return errno;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int AsmProcessFile(Stack* stack, FILE* file)
{
    assert (stack);
    assert (file);

    if (!file || ferror (file))
    {
        errno = errno | PROC_FILE_OPENING_ERR;
        return errno;
    }

    size_t num_symbols = CountSymbols (file);
    char* file_buffer = ReadFileToBuffer (file, num_symbols);
    size_t num_lines = CountLines (file_buffer);

    String** ptr_array = (String**) calloc (num_lines, sizeof (String*));
    String* str_array = (String*) calloc (num_lines, sizeof (String));

    OneginFillPArray (file_buffer, ptr_array, str_array, num_lines, num_symbols);

    for (size_t i = 0; i < num_lines; i ++)
    {   
        AsmParseCommand (stack, ptr_array[i]);
    }

    free (ptr_array);
    free (str_array);
    free (file_buffer);

    return errno;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int ProcDump (Stack* stack)
{
    printf ("ERROR NUM: %d\n", errno);
    StackDump (stack);

    return errno;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int ProcValidate (Stack* stack)
{
    StackValidate (stack, STACK_EXTERNAL_FUNC_CODE);

    return errno;
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

    AsmProcessFile (&stack, file);

    // ProcDump (&stack);

    StackDtor (&stack);


    return errno;
}

