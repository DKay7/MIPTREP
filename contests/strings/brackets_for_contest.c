#include <malloc.h>

#define and &&
#define or ||

typedef int stack_type;
typedef unsigned long long hummingbird_type;

extern const hummingbird_type HUMMINGBIRD;
extern int stack_exit_code;

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

typedef struct Stack
{
    hummingbird_type start_bird;
    stack_type *start;
    int capacity;
    int pointer;
    unsigned long long hash; 
    hummingbird_type end_bird;
} Stack;

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

enum StackExitCodes
{
    STACK_FINE                        = 0x000000,     //  If all is OK
    STACK_MEMORY_ALLOC_ERROR          = 0x100000,     //  Error while allocation memory in functions calloc/realloc
    STACK_INCORRECT_STACK_POINTER     = 0x200000,     //  Incorrect pointer to start of stack buffer
    STACK_INCORRECT_STACK_SIZE        = 0x300000,     //  Size below zero or size more than capacity
    STACK_INCORRCT_STACK_CAPACITY     = 0x400000,     //  Capacity below zero
    STACK_WRONG_START_HUMMINGBIRD     = 0x500000,     //  Changes in start-hummingbird
    STACK_WRONG_END_HUMMINGBIRD       = 0x600000,     //  Changes in end-hummingbird
    STACK_WRONG_HASH_SUM              = 0x700000      //  Mismath with recorded hash-sum
};

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

enum StackFunctionNumbers
{
    STACK_CTOR_CODE       = 1,    //Code of StackCtor()
    STACK_PUSH_CODE       = 2,    //Code of StackPush()
    STACK_POP_CODE        = 3,    //Code of StackPop()
    STACK_VALIDATY_CODE   = 4,    //Code of StackValidaty()
    STACK_INCREASE_CODE   = 5,    //Code of StackIncrease()
    STACK_DECREASE_CODE   = 6,    //Code of StackDecrease()
    STACK_DUMP_CODE       = 7     //Code of macro StackDump()
};

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void StackPush(Stack*, stack_type);
stack_type StackPop(Stack*);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

Stack *StackCtor(int);
int StackValidity(Stack*, const int);
unsigned long long HashSum(Stack*);
void StackPrintExitCode ();
//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int StackIncrease(Stack*);
int StackDecrease(Stack*);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
void StackUnitTest ();
int StackDumpFunction(Stack*, const char*, int, const char*, const char* );
#define StackDump(stack) StackDumpFunction (stack, __PRETTY_FUNCTION__, __LINE__, __FILE__, #stack);
#include <assert.h>
#include <stdio.h>

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
const hummingbird_type HUMMINGBIRD = (hummingbird_type) 0xBADDED;
int stack_exit_code = 0;

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

Stack *StackCtor(int size)
{   
    assert(size > 0);
    
    Stack *stack = (Stack*) calloc(1, sizeof(Stack));
    stack_type* tmp_start = (stack_type*) calloc(size, sizeof(stack_type));

    if(stack == NULL or tmp_start == NULL)
    {
        stack_exit_code = STACK_MEMORY_ALLOC_ERROR + STACK_CTOR_CODE;
        return NULL;
    }

    stack->start_bird = HUMMINGBIRD;
    stack->start = tmp_start;
    stack->pointer = 0;
    stack->capacity = size;
    // stack->hash = HashSum(stack);
    stack->end_bird = HUMMINGBIRD;

    return stack;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void StackPush(Stack *stack, stack_type element)
{   
    assert(stack != NULL);

    // if(!StackIncrease(stack))  
    //     return;


    *(stack->start + stack->pointer) = element;
    stack->pointer += 1;
    // stack->hash = HashSum(stack);

}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

stack_type StackPop(Stack *stack)
{    
    assert(stack != NULL);

    stack_type element = 0;

    if (stack->pointer >= 1)
    {
        stack->pointer -= 1;
    }

    element = *(stack->start + stack->pointer);
    *(stack->start + stack->pointer) = 0;

    // StackDecrease(stack);
    // stack->hash = HashSum(stack);

    return element;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int StackIncrease(Stack *stack)
{   
    assert(stack != NULL);

    stack_type* tmp_start;
    
    if(stack->pointer + 1 > stack->capacity)
    {

        tmp_start = (stack_type*) realloc(stack->start, 2 * stack->capacity * sizeof(Stack));

        if(tmp_start == NULL){
            stack_exit_code = STACK_MEMORY_ALLOC_ERROR + STACK_INCREASE_CODE;
            return 0;
        }

        stack->start = tmp_start;
        stack->capacity = 2*stack->capacity;
    }

    return 1;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int StackDecrease(Stack *stack)
{   
    assert(stack != NULL);

    stack_type *tmp_start;

    if( 2 * (stack->pointer - 1) < stack->capacity)
    {
        tmp_start = (stack_type*) realloc(stack->start, 
                                            (2/3 + 1) * 
                                            stack->capacity * 
                                            sizeof(Stack));

        if(tmp_start == NULL)
        {
            stack_exit_code = STACK_DECREASE_CODE + STACK_MEMORY_ALLOC_ERROR;
            return 0;
        } 
        
        stack->start = tmp_start;
        stack->capacity = stack->capacity / 3 * 2 + 1;
    }

    return 1;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int StackValidity(Stack *stack, const int func_code)
{
    if(stack->start == NULL)
    {
        stack_exit_code = STACK_INCORRECT_STACK_POINTER + func_code;
        return 0;
    }

    if(stack->start_bird != HUMMINGBIRD)
    {
        stack_exit_code = STACK_WRONG_START_HUMMINGBIRD + func_code;
        return 0;
    }

    if(stack->start_bird != HUMMINGBIRD)
    {
        stack_exit_code = STACK_WRONG_END_HUMMINGBIRD + func_code;
        return 0;
    }

    if(stack->pointer > stack->capacity or stack->pointer < 0)
    {
        stack_exit_code = STACK_INCORRECT_STACK_POINTER + func_code;
        return 0;
    }

    if(stack->capacity < 0)
    {
        stack_exit_code = STACK_INCORRCT_STACK_CAPACITY + func_code;
        return 0;
    }

    if(stack->hash != HashSum(stack))
    {
        stack_exit_code = STACK_WRONG_HASH_SUM + func_code;
        return 0;
    }


    return 1;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int StackDumpFunction(Stack *stack, const char *func_name, int line_number, const char *file_name, const char *stack_name)
{   
    int check = StackValidity(stack, STACK_DUMP_CODE);

    if(check)
    {
        printf ("Stack[OK]: ");
    }

    else
    {
        printf ("Stack[ERROR][CODE: 0x%X]", stack_exit_code);
    }

    printf ("[%p] ", &stack->start);

    printf ("\"%s\" %s line %d %s'\n", stack_name, func_name, line_number, file_name);

    if(!check)
        StackPrintExitCode();

    printf ("\n{\n");              
                                                
    printf (" size = %u \n", stack->pointer);           
                                                    
    printf (" capacity = %u\n", stack->capacity);    
                                                    
    printf (" hash_sum = %llX\n", stack->hash);       
                                                    
    printf ("\t{\n"); 

    for (size_t i=0; i< stack->capacity; i++)
    {
        printf ("   ");      

        if (i < stack->pointer)                        
            printf  ("\t *");                      
        else                                        
            printf ("\t  ");

        printf  ("[%lu] = %d \n", i, *(stack->start + i)); 
    }

    printf ("   }\n}\n"); 

    return 0;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

unsigned long long HashSum(Stack* stack)
{
    assert(stack != NULL);

    unsigned long long hash = 0;

    for (unsigned i=0; i < stack->pointer; i++)
    {
        hash += *(stack->start + i);
        hash <<= sizeof(stack_type);
    }

    return hash;
}

void StackPrintExitCode ()
{   
    int func_code = stack_exit_code % 256;
    int err_code = stack_exit_code - func_code;
    
    if (err_code == STACK_FINE)
    {
        printf ("No errors founded\n");
        return;
    }

    switch (err_code)
    {
        case STACK_MEMORY_ALLOC_ERROR:
            printf ("Memory allocation error in ");
            break;
    
        case STACK_INCORRECT_STACK_POINTER:
            printf ("Incorrect pointer to start of buffer founded in ");
            break;

        case STACK_INCORRECT_STACK_SIZE:
            printf ("Stack size below zero or stack overdlow exception founded in ");
            break;

        case STACK_INCORRCT_STACK_CAPACITY:
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

    return;
}

void StackUnitTest ()
{
    Stack stack1 = *StackCtor(50);
    Stack stack2 = *StackCtor(50);
    Stack stack3 = *StackCtor(50);

    char test1[] = "PRESS F TO PAY RESPECTS";
    char test2[] = "HAHA OFIGENNO";
    char test3[] = "42 or 97 hmmmmmmmm";

    for (int i = 0; test1[i]; i++)
        StackPush (&stack1, test1[i]);

    for (int i = 0; test2[i]; i++)
        StackPush (&stack2, test2[i]);

    for (int i = 0; test3[i]; i++)
        StackPush (&stack3, test3[i]);

    StackDump (&stack1);
    StackDump (&stack2);
    StackDump (&stack3);

    StackPop (&stack1);
    StackPop (&stack2);
    StackPop (&stack3);

    printf("AFTER POPING:\n");

    StackDump (&stack1);
    StackDump (&stack2);
    StackDump (&stack3);

}

#include <stdio.h>


typedef char stacktype;

int check_bracket(char open_bracket, char close_bracket)
{
    return open_bracket == close_bracket;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int main()
{
    Stack* stack = StackCtor(100000);
    char bracket = 0;
    char open_bracket = 0;
    char checker = 1;

    while ((bracket = getchar()) != '\n')
    {   
        switch (bracket)
        {
        case '{':
            StackPush (stack, bracket);
            break;
        case '}':
            open_bracket = StackPop (stack);
            checker = check_bracket (open_bracket, '{');
            break;
        case '(':
            StackPush (stack, bracket);
            break;
        case ')':
            open_bracket = StackPop (stack);
            checker = check_bracket (open_bracket, '(');
            break;
        case '[':
            StackPush (stack, bracket);
            break;
        case ']':
            open_bracket = StackPop (stack);
            checker = check_bracket (open_bracket, '[');

            break;
        case '<':
            StackPush (stack, bracket);
            break;
        case '>':
            open_bracket = StackPop (stack);
            checker = check_bracket (open_bracket, '<');
            break;

        default:
            printf ("NO\n");
            free(stack->start);
            free (stack);
            return 0;
        }

        if (!checker)
        {
            printf ("NO\n");
            free(stack->start);
            free (stack);
            return 0;
        }

    }
    
    if (stack->pointer != 0)
    {   
        printf ("NO\n");
    }


    if (stack->pointer == 0)
    {
        printf ("YES\n");
    }

    free(stack->start);
    free (stack);

    return 0;
}