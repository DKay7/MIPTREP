#include "stack.h"
#include <string.h>

void printer_int (FILE* file, int value)
{
    fprintf (file, "%d", value);
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void printer_str (FILE* file, char* value)
{   
    fprintf (file, "%s", value);
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int main()
{    
    Stack<int> int_stack = {};
    Stack<char*> str_stack = {};

    // FILE* log = fopen ("stack.log", "wa+");

    StackCtor<int>   (&int_stack, 1, printer_int);
    StackCtor<char*> (&str_stack, 1, printer_str);

    StackDump<int>  (&int_stack);
    StackDump<char*>(&str_stack);

    printf ("\n--------------------------\nPUSH TEST\n--------------------------");
    for (int i = 0; i < 7; i++)
    {   
        int int_value_to_push = (i << 7)  - 43;
        char* str_value_to_push = (char*) calloc (50, sizeof (char));
        sprintf (str_value_to_push, "%d ABOBA %d", i, i);

        StackPush(&int_stack, int_value_to_push);
        StackPush(&str_stack, str_value_to_push);
    }

    StackDump<int>  (&int_stack);
    StackDump<char*>(&str_stack);
    
    printf ("\n--------------------------\nPEEK TEST\n--------------------------\n");
    printf ("peeked int value: %d\n", StackPeek (&int_stack));
    printf ("peeked int value: %s\n", StackPeek (&str_stack));
   
    printf ("\n--------------------------\nPOP TEST\n--------------------------\n");
    for (int i = 0; i < 7; i++)
    {   
        int   int_element = StackPop(&int_stack);
        char* str_element = StackPop(&str_stack);
        printf ("poped int value: %d\n", int_element);
        printf ("poped str value: %s\n", str_element);
        free (str_element);
    }

    printf ("\n--------------------------\nPOP TEST DUMP\n--------------------------\n");
    StackDump<int>  (&int_stack);
    StackDump<char*>(&str_stack);  


    StackDtor (&int_stack);
    StackDtor (&str_stack);

    return 0;
}