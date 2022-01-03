#include "differentiator.h"
#include <malloc.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdint.h>
#include <string.h>

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

Node* NodeCtor (NODE_TYPES type, data_t data)
{   
    Node* node = (Node*) calloc (1, sizeof (*node));
    ASS (node != NULL, NULL);

    node->type = type;
    node->data = data;

    return node;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void NodeDtor (Node* node)
{
    assert (node);

    Node* left_chld  = node->left;
    Node* right_chld = node->right;

    node->type   = INV_T;
    node->left   = NULL;
    node->right  = NULL;
    node->data.operator_   = INVALID;

    free (node);

    if (left_chld)
    {
        NodeDtor (left_chld);
    }

    if (right_chld)
    {
        NodeDtor (right_chld);
    }

    return;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int TreeCtor (Tree* tree)
{   
    assert (tree);

    tree->root   = NULL;
    tree->size   = 0;
    tree->errno_ = DIFF_OK;
    
    return tree->errno_;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void TreeDtor (Tree* tree)
{
    assert (tree);

    if (tree->root)
    {
        NodeDtor (tree->root);
    }

    tree->size = 0;
    tree->root = NULL;

    return;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void TreeDump (Tree* tree)
{
    assert (tree);

    char filename_dot[] = "/tmp/dot_fileXXXXXX";
    char filename_out[] = "/tmp/png_fileXXXXXX";

    int dot_fd = mkstemp (filename_dot);
    int out_fd = mkstemp (filename_out);

    ASS (dot_fd != -1, (void) 0);
    ASS (out_fd != -1, (void) 0);

    FILE* dot_file = fdopen (dot_fd, "w");
    fprintf (dot_file,  "digraph {\n rankdir = HR;\n node[shape=box]\n");

    if (tree->root)
    {   
        NodeDump (tree->root, dot_file);
    }

    else
    {
        fprintf (dot_file, "\"В дереве нет элементов\"\n");
    }

    fprintf (dot_file, "\n}");
    fclose (dot_file);

    char compile_cmd[128];
    char open_cmd[128];

    sprintf (compile_cmd, "dot -Tpng %s -o %s", filename_dot, filename_out);
    sprintf (open_cmd, "xdg-open %s 2> /dev/null", filename_out);

    printf("\n"
           "[имя dot-файла:\t%s]\n"
           "[имя png-файла:\t%s]\n\n", 
            filename_dot, filename_out);


    ASS (system (compile_cmd) == 0, (void) 0);
    ASS (system (open_cmd)    == 0, (void) 0);

    return;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void NodeDump (Node* node, FILE* dump_file)
{
    assert (node);
    assert (dump_file);
    
    const uintptr_t node_ptr = (uintptr_t) node;

    fprintf (dump_file, 
             "node_%lu ["
             "style=\"rounded, filled\",",
             node_ptr);

    switch (node->type)
    {   
        case OPERATOR:
            fprintf (dump_file, "fillcolor = green, label = \"%s\"];\n", OperatorToStr (node->data.operator_));
            break;

        case VARIABLE:
            fprintf (dump_file, "fillcolor = red, label = \"%c\"];\n", node->data.variable_);
            break;

        case CONSTANT:
            fprintf (dump_file, "fillcolor = blue, label = \"%lf\"];\n", node->data.constant_);
            break;
        
        case INV_T:
        default:
            fprintf (dump_file, "fillcolor = white, label = \"Invalid (or unknown) node type\"];\n");
            break;
    }

    if (node->left)
    {   
        NodeDump (node->left, dump_file);
        fprintf (dump_file, "node_%lu -> node_%lu;\n",
                 node_ptr, (uintptr_t) node->left);
    }

    if (node->right)
    {
        NodeDump (node->right, dump_file);
        fprintf (dump_file, "node_%lu -> node_%lu;\n",
                 node_ptr, (uintptr_t) node->right);
    }


    return;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

const char* OperatorToStr (OPERATORS op)
{
    switch (op)
    {
        #define OP_DEF(enum_name, repr, ...) \
            case (enum_name):                \
                return repr;
            
        #include "operators.h"
        #undef OP_DEF

        default:
            return "Unknown operator";
            break;
    }
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
