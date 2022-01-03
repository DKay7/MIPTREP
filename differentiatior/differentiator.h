#include <stdio.h>
#include <math.h>
#include "text_lib/texlib.h"

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

#define ASS(cond, ret)                                                  \
    if(!(cond))                                                         \
    {                                                                   \
        fprintf (stderr, "Soft assertation ( " #cond " ) has failed "   \
                         "in file %s:%d \n", __FILE__, __LINE__);       \
        return ret;                                                     \
    }

#define TERMINATOR_SYMBOL '\0'
#define DEPTH_LEEVEL_MAX 5
#define RANDOM_PROBABILITY 70

#define L cur_node->left
#define R cur_node->right

#define DL DiffSubtree (cur_node->left,  size, latex)
#define DR DiffSubtree (cur_node->right, size, latex)

#define CR CopySubtree (cur_node->right, size)
#define CL CopySubtree (cur_node->left,  size)

#define UNITE(OP, left, right)  UniteSubtreesWithOperator ((OP), (left), (right))

#define NEW_C(const) NodeCtor (CONSTANT, { .constant_ = (const) })
#define NEW_V(var  ) NodeCtor (VARIABLE, { .variable_ = (var  ) })
#define NEW_O(op   ) NodeCtor (OPERATOR, { .operator_ = (op   ) })

#define MOVE_SUBTREE(left_or_right)             \
    {                                           \
        Node* node_to_delete = cur_node;        \
        cur_node = cur_node->left_or_right;     \
        node_to_delete->left_or_right = NULL;   \
        NodeDtor (node_to_delete);              \
    }

#define REPLACE_SUBTREE(constant)               \
    {                                           \
        Node* new_node = NEW_C ((constant));    \
        NodeDtor (cur_node);                    \
        cur_node = new_node;                    \
    }

#define EQUALS(first_term, second_term)         \
    (fabs ((first_term) - (second_term)) < 1e-5)

#define MAX(a, b)              \
({                             \
        __typeof__(a) __a = a; \
        __typeof__(b) __b = b; \
        __a > __b ? __a : __b; \
})


//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

enum DIFF_ERRORS
{
    DIFF_OK                 = 0x01,
    DIFF_MEM_ALLOK_ERR      = 0x02,
    DIFF_PARSING_ERROR      = 0x04,
};

enum NODE_TYPES
{   
    INV_T       = 0,
    OPERATOR    = 1,
    VARIABLE    = 2,
    CONSTANT    = 3,
};

enum OPERATORS
{   
    #define OP_DEF(enum_name,repr, ...) \
            enum_name,
    
    #include "operators.h"

    #undef OP_DEF
};

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

typedef union
{
    OPERATORS   operator_;
    double      constant_;
    char        variable_;
} data_t;

typedef struct Node
{   
    bool need_replacement;
    char replacement_letter;
    NODE_TYPES type;
    
    data_t data;
    Node*  left;
    Node*  right;
} Node;

typedef struct
{
    size_t size;
    DIFF_ERRORS errno_;
    Node* root;
} Tree;

typedef struct 
{
    Text  init;
    Text  close;
    Text  trans_phrases;
    Text  final_phrases;
    FILE* print_to;
    char  filename[32];
} Latex;

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

double ComputeTree (Node* cur_node, double* vars_table);
double GetFromVarsTable (char var, double* vars_table);
void AddToVarsTable (char var, double value, double* vars_table);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void  DiffTree (Tree* tree, Tree* new_tree, Latex* latex);
Node* DiffSubtree (Node* cur_node, size_t* size, Latex* latex);

Node* CopySubtree (Node* root_to_copy, size_t* size);
Node* UniteSubtreesWithOperator (OPERATORS operator_, Node* left_subtree, Node* right_subtree);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void SimplifyTree (Tree* tree, Latex* latex);
void SimplifySubtree(Node** node, Latex* latex);
bool SimplifySubtreeOneStage (Node** node, Latex* latex);


void RecountTreeSize (Node* cur_node, size_t* size);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void LatexCtor (Latex* latex);
void LatexDtor (Latex* latex);
void InitTexPrint (Latex* latex, Node* node);
void EndTexPrint (Latex* latex, Node* node);
void PrintDifferentiationToTex (Latex* latex, Node* prev_node, Node* cur_node);
void PrintSimplificationToTex (Latex* latex, Node* prev_node, Node* cur_node);
void PrintNodeToTex (Node* cur_node, FILE* latex);
bool FindNodesToReplace (Node* cur_node, int* cur_depth, char* replacement_letter);
void PrintReplacementNotation (Latex* latex, Node* cur_node);
int GetOperatorPriority (Node* node);
void IsBracketsNedeed (Node* cur_node, bool* need_l_brackets, bool* need_r_brackets);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

Node* NodeCtor (NODE_TYPES type, data_t data);
void  NodeDtor (Node* node);
int   TreeCtor (Tree* tree);
void  TreeDtor (Tree* tree);

void TreeDump (Tree* tree);
void NodeDump (Node* node, FILE* dump_file);
const char* OperatorToStr (OPERATORS op);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

bool ReadTree (Tree* tree, FILE* file_to_read);

bool GetGrammar (char* str, Node** cur_node, size_t* size);
bool GetExpression (char** cur_ptr, Node** cur_node, size_t* size);
bool GetTerm (char** cur_ptr, Node** cur_node, size_t* size);
bool GetPower (char** cur_ptr, Node** cur_node, size_t* size);
bool GetUnary (char** cur_ptr, Node** cur_node, size_t* size);
bool GetParentheses (char** cur_ptr, Node** cur_node, size_t* size);

bool GetNumber (char** cur_ptr, double* number);
bool GetInteger (char** cur_ptr, long long int* number, int* power);
bool GetDigit (char** cur_ptr, int* digit);

bool Required (char** cur_str, char symbol);
void SkipTabs (char** cur_ptr);
void SyntaxError(const char* str);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
