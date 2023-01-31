#include "differentiator.h"
#include <malloc.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include <math.h>
#include <ctype.h>

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

bool ReadTree (Tree* tree, FILE* file_to_read)
{   
    assert (tree);

    char* cur_str = NULL;
    fscanf (file_to_read, "%m[^\n]s", &cur_str);
    ASS (cur_str, NULL);

    Node* root = NULL;
    size_t size = 0;

    bool is_ok = GetGrammar (cur_str, &root, &size);

    
    if (is_ok)
    {
        tree->root = root; 
        tree->size = size;
    }

    else
    {
        tree->root = NULL;
        tree->size = 0;
        tree->errno_ = DIFF_PARSING_ERROR;
    }

    free (cur_str);
    cur_str = NULL;

    return is_ok;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

bool GetGrammar (char* cur_ptr, Node** cur_node, size_t* size)
{   
    assert (cur_ptr);

    bool is_ok = GetExpression (&cur_ptr, cur_node, size);
    bool is_termnator_char = Required (&cur_ptr, TERMINATOR_SYMBOL);

    if (!is_termnator_char)
    {
        SyntaxError ("Can't find terminator char");
    }

    return is_ok && is_termnator_char;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

bool GetExpression (char** cur_ptr, Node** cur_node, size_t* size)
{   
    assert (cur_ptr);
    assert (cur_node);

    SkipTabs (cur_ptr);

    Node* left_tree = NULL;
    bool is_ok = GetTerm (cur_ptr, &left_tree, size);
    SkipTabs (cur_ptr);
    
    if (Required (cur_ptr, '+'))
    {   
        *cur_node = NodeCtor (OPERATOR, { .operator_ = ADD });
        (*cur_node)->left = left_tree;
        (*size) ++;

        is_ok = is_ok && GetExpression (cur_ptr, &(*cur_node)->right, size);
    }

    else if (Required (cur_ptr, '-'))
    {   
        *cur_node = NodeCtor (OPERATOR, { .operator_ = SUB });
        (*cur_node)->left = left_tree;
        (*size)++;

        is_ok = is_ok && GetExpression (cur_ptr, &(*cur_node)->right, size);
    }

    else
    {
        (*cur_node) = left_tree;
    }

    return is_ok;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

bool GetTerm (char** cur_ptr, Node** cur_node, size_t* size)
{
    assert (cur_ptr);
    assert (cur_node);
    SkipTabs (cur_ptr);

    Node* left_tree = NULL;
    bool is_ok = GetPower (cur_ptr, &left_tree, size);
    SkipTabs (cur_ptr);
    
    if (Required (cur_ptr, '*'))
    {   
        *cur_node = NodeCtor (OPERATOR, { .operator_ = MUL });
        (*cur_node)->left = left_tree;
        (*size)++;

        is_ok = is_ok && GetTerm (cur_ptr, &(*cur_node)->right, size);
    }

    else if (Required (cur_ptr, '/'))
    {   
        *cur_node = NodeCtor (OPERATOR, { .operator_ = DIV });
        (*cur_node)->left = left_tree;
        (*size)++;
        
        is_ok = is_ok && GetTerm (cur_ptr, &(*cur_node)->right, size);
    }

    else
    {
        (*cur_node) = left_tree;
    }

    return is_ok;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

bool GetPower (char** cur_ptr, Node** cur_node, size_t* size)
{
    assert (cur_ptr);
    assert (cur_node);
    SkipTabs (cur_ptr);

    Node* left_tree = NULL;
    bool is_ok = GetUnary (cur_ptr, &left_tree, size);
    SkipTabs (cur_ptr);
    
    if (Required (cur_ptr, '^'))
    {   
        *cur_node = NodeCtor (OPERATOR, { .operator_ = POW });
        (*cur_node)->left = left_tree;
        (*size)++;
        
        is_ok = is_ok && GetPower (cur_ptr, &(*cur_node)->right, size);
    }

    else
    {
        (*cur_node) = left_tree;
    }

    return is_ok; 
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

bool GetUnary (char** cur_ptr, Node** cur_node, size_t* size)
{
    assert (cur_ptr);
    assert (cur_node);
    SkipTabs (cur_ptr);

    #define UNARY(enum_name, str_name, ...)                                     \
        if (strncmp (*cur_ptr, str_name, strlen (str_name)) == 0)               \
        {                                                                       \
            *cur_ptr += strlen (str_name);                                      \
            *cur_node = NodeCtor (OPERATOR, { .operator_ = enum_name });        \
            (*size)++;                                                          \
            bool is_ok = GetUnary (cur_ptr, &(*cur_node)->left, size);          \
            return is_ok;                                                       \
                                                                                \
        } else                                           
    
    #include "operators.h"

    // last else
    {   
        bool is_ok = GetParentheses (cur_ptr, cur_node, size);

        return is_ok;
    }
    
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

bool GetParentheses (char** cur_ptr, Node** cur_node, size_t* size)
{
    assert (cur_ptr);
    assert (cur_node);
    SkipTabs (cur_ptr);
    
    if (Required (cur_ptr, '('))
    {
        bool is_ok = GetExpression (cur_ptr, cur_node, size);
        bool is_close_bracket = Required (cur_ptr, ')');

        if (!is_close_bracket)
        {
            SyntaxError ("Can't find closing bracket");
        }

        return is_ok && is_close_bracket;
    }

    else if (isalpha (**cur_ptr))
    {   
        *cur_node = NodeCtor (VARIABLE, { .variable_ = **cur_ptr });
        (*size)++;
        (*cur_ptr)++;
        return true;
    }

    else
    {   
        double num = 0;
        bool is_ok = GetNumber (cur_ptr, &num);

        *cur_node = NodeCtor (CONSTANT, { .constant_ = num });
        (*size)++;
        return is_ok;
    }
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
bool GetNumber (char** cur_ptr, double* number)
{   
    assert (cur_ptr);

    SkipTabs (cur_ptr);
    const char* old_s = *cur_ptr;

    while ('0' <= **cur_ptr && **cur_ptr <= '9')
    {
        *number = 10 * (*number) + (**cur_ptr) - '0';
        (*cur_ptr)++;
    }

    if (**cur_ptr == '.')
    {   
        (*cur_ptr) ++;

        const char* fractional_start = (*cur_ptr);
        double ten_in_power = 1;

        while ('0' <= **cur_ptr && **cur_ptr <= '9')
        {
            (*number) = 10 * (*number) + (**cur_ptr) - '0';
            ten_in_power *= 10;

            (*cur_ptr)++;
        }

        (*number) /= ten_in_power;

        if (fractional_start == (*cur_ptr))
        {
            SyntaxError("Number required");
            return false;
        }
    }

    if (old_s == (*cur_ptr))
    {
        SyntaxError("Number required");
        return false;
    }

    return true;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

bool Required (char** cur_str, char symbol)
{
    if (**cur_str == symbol)
    {
        (*cur_str) ++;
        return true;
    }

    return false;
}
//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void SkipTabs (char** cur_ptr)
{   
    assert (cur_ptr);

    while (**cur_ptr == ' ')
    {
        (*cur_ptr)++;
    }

    return;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void SyntaxError(const char* str)
{
    assert (str);

    fprintf (stderr, "Syntax error while reading: %s\n", str);
    return;
}