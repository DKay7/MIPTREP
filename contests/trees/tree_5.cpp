#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

#define ASS(cond, ret)                                                  \
    if(!(cond))                                                         \
    {                                                                   \
        fprintf (stderr, "Soft assertation ( " #cond " ) has failed "   \
                         "in file %s:%d \n", __FILE__, __LINE__);       \
        return ret;                                                     \
    }

#define MAX(a, b) ({             \
        __typeof__(a) __a = (a); \
        __typeof__(b) __b = (b); \
        (__a > __b) ? __a : __b; \
    })

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

typedef struct Node
{
    int data;
    struct Node* left;
    struct Node* right;
    int depth;
    int is_balansed;
} Node;

Node* NodeCtor (int data);
void NodeDtor (Node* node);
Node* InsertData (Node* cur_node, int data);
bool CheckTreeBalance (Node* cur_node);
void TreeDump (Node* node);
void NodeDump (Node* node, FILE* dump_file);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int main ()
{   
    int next_d = -1;
    Node* root = NULL;

    while (true)
    {   
        int readed = scanf ("%d", &next_d);

        if (next_d == 0 || readed <= 0)
        {
            break;
        }

        root = InsertData (root, next_d);
    }

    bool is_balanced = CheckTreeBalance (root);
    
    if (is_balanced)
    {
        printf ("YES\n");
    }
    
    else
    {
        printf ("NO\n");
    }

    NodeDtor (root);

    return 0;
}

Node* NodeCtor (int data)
{
    Node* node = (Node*) calloc (1, sizeof (*node));
    node->data = data;
    node->depth = -1;
    node->is_balansed = -1;

    return node;
}

void NodeDtor (Node* node)
{   
    if (!node)
        return;
    
    if (node->left)
    {
        NodeDtor (node->left);
    }
    
    if (node->right)
    {
        NodeDtor (node->right);
    }

    free (node);
    node = NULL;
    return;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

Node* InsertData (Node* cur_node, int data)
{   
    if (cur_node == NULL)
    {   
        return NodeCtor (data);
    }

    if (data > cur_node->data)
    {
        cur_node->right = InsertData (cur_node->right, data);
    }

    else if (data < cur_node->data)
    {
        cur_node->left = InsertData (cur_node->left, data);
    }

    return cur_node;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int GetSubtreeDepth(Node* current_node) {

    if (current_node == NULL)
        return 0;

    if (current_node->depth != -1)
        return current_node->depth;
    
    current_node->depth = MAX(GetSubtreeDepth(current_node->left),
                              GetSubtreeDepth(current_node->right)) + 1;

    return current_node->depth;
}


bool CheckTreeBalance (Node* current_node)
{   
    if (current_node == NULL)
        return true;

    if (current_node->is_balansed != -1)
        return current_node->is_balansed;

    int left_size  = GetSubtreeDepth(current_node->left),
        right_size = GetSubtreeDepth(current_node->right);

    if (abs(left_size - right_size) > 1)
    {    
        current_node->is_balansed = false;
        return current_node->is_balansed;
    }

    current_node->is_balansed = CheckTreeBalance(current_node->left) && 
                                CheckTreeBalance(current_node->right);

    return current_node->is_balansed;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void TreeDump (Node* node)
{
    char filename_dot[] = "/tmp/dot_fileXXXXXX";
    char filename_out[] = "/tmp/png_fileXXXXXX";

    int dot_fd = mkstemp (filename_dot);
    int out_fd = mkstemp (filename_out);

    ASS (dot_fd != -1, (void) 0);
    ASS (out_fd != -1, (void) 0);

    FILE* dot_file = fdopen (dot_fd, "w");
    fprintf (dot_file,  "digraph {\n rankdir = HR;\n node[shape=box]\n");

    if (node)
    {   
        NodeDump (node, dot_file);
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
    ASS (system (open_cmd) == 0, (void) 0);

    return;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void NodeDump (Node* node, FILE* dump_file)
{    
    const uintptr_t node_ptr = (uintptr_t) node;

    fprintf (dump_file, 
             "node_%lu ["
             "style=\"rounded, filled\","
             "fillcolor = green, label = \"Data: %d\\nDepth: %d\"];\n",
             node_ptr, node->data, node->depth);

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
