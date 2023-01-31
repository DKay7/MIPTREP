#include "differentiator.h"
#include <assert.h>
#include <stdio.h>
#include <malloc.h>
#include <math.h>
#include <ctype.h>

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int main ()
{   
    Tree tree = {};
    Tree diff_tree = {};
    Latex latex = {};

    LatexCtor (&latex);
    TreeCtor(&tree);

    ASS (ReadTree (&tree, stdin), 0);
    printf ("Size: %lu\n", tree.size);
    TreeDump (&tree);

    InitTexPrint (&latex, tree.root);
// 
    DiffTree (&tree, &diff_tree, &latex);
    TreeDump (&diff_tree);

    SimplifyTree (&diff_tree, &latex);
    TreeDump (&diff_tree);
    printf ("New Size: %lu\n", diff_tree.size);
    
    EndTexPrint (&latex, diff_tree.root);

    TreeDtor (&tree);
    TreeDtor (&diff_tree);
    LatexDtor (&latex);
    
    return 0;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

double ComputeTree (Node* cur_node, double* vars_table)
{
    assert (cur_node);
    assert (vars_table);

    switch (cur_node->type)
    {
        case OPERATOR:
            
            switch (cur_node->data.operator_)
            {
                #define OP_DEF(enum_name, repr, computation, ...)  \
                    case enum_name:                                \
                        computation
                        break;

                #include "operators.h"
                #undef OP_DEF

                default:
                    ASS (false, 0);
            }

            break;

        case VARIABLE:
            return GetFromVarsTable (cur_node->data.variable_, vars_table);

        case CONSTANT:
            return cur_node->data.constant_;
        
        case INV_T:
        default:
            ASS (false, 0);

    }

    
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void DiffTree (Tree* tree, Tree* new_tree, Latex* latex)
{
    assert (tree);
    assert (latex);
    assert (tree->root);

    size_t new_size = 0;
    Node* new_tree_root = DiffSubtree (tree->root, &new_size, latex);
    
    TreeDtor (tree);
    TreeCtor (new_tree);
    
    new_tree->root = new_tree_root;
    new_tree->size = new_size;

    return;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

Node* DiffSubtree (Node* cur_node, size_t* size, Latex* latex)
{   
    assert (cur_node);
    assert (size);
    assert (latex);

    Node* return_node = NULL;

    switch (cur_node->type)
    {
        case OPERATOR:

            switch (cur_node->data.operator_)
            {
                #define OP_DEF(enum_name, repr, computation, diff, ...)  \
                    case enum_name:                                      \
                        diff

                #include "operators.h"
                #undef OP_DEF

                default:
                    ASS (false, NULL);
                    break;
            }

            break;

        case VARIABLE:
            (*size) += 1;
            return_node = NEW_C (1);
            break;
        
        case CONSTANT:
            (*size) += 1;
            return_node = NEW_C (0);
            break;
        
        case INV_T:
        default:
            return_node = NULL;
            break;
    }

    PrintDifferentiationToTex (latex, cur_node, return_node);

    return return_node;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void SimplifyTree (Tree* tree, Latex* latex)
{
    assert (tree);
    assert (tree->root);

    SimplifySubtree (&tree->root, latex);
    tree->size = 0;
    RecountTreeSize (tree->root, &tree->size);
    
    return;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void SimplifySubtree(Node** node, Latex* latex)
{
    while (SimplifySubtreeOneStage(node, latex));
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

bool SimplifySubtreeOneStage (Node** node, Latex* latex)
{   
    #define cur_node ( *node )
    
    Node* old_node = cur_node;

    if (!node || !cur_node || cur_node->type != OPERATOR)
        return false;

    SimplifySubtreeOneStage (&L, latex);
    SimplifySubtreeOneStage (&R, latex);
    
    switch (cur_node->data.operator_)
    {
        #define OP_DEF(enum_name, str_name, computation, diff, simplificator, ...)   \
            case enum_name:                                                          \
                    simplificator                                                    

        #include "operators.h"
        #undef OP_DEF

        default:
            return false;
    }

    PrintSimplificationToTex (latex, old_node, cur_node);

    #undef cur_node

}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void RecountTreeSize (Node* cur_node, size_t* size)
{
    assert (cur_node);
    assert (size);

    (*size) ++;

    if (cur_node->left)
    {
        RecountTreeSize (cur_node->left, size);
    }

    if (cur_node->right)
    {
        RecountTreeSize (cur_node->right, size);
    }

    return;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

Node* CopySubtree (Node* root_to_copy, size_t* size)
{   
    assert (root_to_copy);

    Node* new_node = NodeCtor (root_to_copy->type, root_to_copy->data);
    (*size) ++;

    if (root_to_copy->left)
    {
        new_node->left = CopySubtree (root_to_copy->left, size);
    }

    if (root_to_copy->right)
    {
        new_node->right = CopySubtree (root_to_copy->right, size);
    }

    return new_node;
}

Node* UniteSubtreesWithOperator (OPERATORS operator_, Node* left_subtree, Node* right_subtree)
{   
    assert (left_subtree);

    Node* new_node = NodeCtor (OPERATOR, { .operator_ = operator_ });
    new_node->left = left_subtree;
    new_node->right = right_subtree;

    return new_node;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void AddToVarsTable (char var, double value, double* vars_table)
{
    assert (vars_table);

    vars_table [tolower (var) - 'a'] = value;

    return;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

double GetFromVarsTable (char var, double* vars_table)
{
    assert (vars_table);

    return vars_table [tolower (var) - 'a'];
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
