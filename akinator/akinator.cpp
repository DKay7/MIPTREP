#include "akinator.h"
#include <assert.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#include <festival/festival.h>
#include <stdarg.h>
#include <wchar.h>
#include <stdio.h>

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int SOUND = true;

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

Node* NodeCtor (const char* data)
{   
    assert (data);

    Node* node = (Node*) calloc (1, sizeof (*node));
    ASS (node != NULL, NULL);
    
    node->object = (char*) calloc (strlen (data) + 1, sizeof (char));    
    ASS (node->object != NULL, NULL);

    strcpy (node->object, data);
    node->left  = NULL;
    node->right = NULL;
    node->prev  = NULL;

    return node;
} 

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void NodeDtor (Node* node)
{   
    assert (node);

    Node* left_chld  = node->left;
    Node* right_chld = node->right;

    free (node->object);
    node->object = NULL;
    node->left   = NULL;
    node->right  = NULL;
    node->prev   = NULL;
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

    tree->root  = NULL;
    tree->size  = 0;
    tree->errno_ |= AK_OK;

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

Node* TreeInsertRoot (Tree* tree, const char* data)
{
    assert (tree);
    
    Node* root = NodeCtor (data);
    ASS (root, NULL);
    tree->root = root;
    tree->size += 1;

    return root;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

Node* TreeInsertLeft (Tree* tree, Node* node_to_ins_after, const char* data)
{   
    assert (data);                     
    assert (tree);                     
    assert (tree->root);               
    assert (tree->size > 0);           
    assert (node_to_ins_after);        
    assert (node_to_ins_after->object);

    Node* new_node = NodeCtor (data);
    ASS (new_node, NULL);

    node_to_ins_after->left = new_node;
    new_node->prev = node_to_ins_after;
    tree->size += 1;

    return new_node; 
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

Node* TreeInsertRight (Tree* tree, Node* node_to_ins_after, const char* data)
{
    assert (data);                     
    assert (tree);                     
    assert (tree->root);               
    assert (tree->size > 0);           
    assert (node_to_ins_after);        
    assert (node_to_ins_after->object);

    Node* new_node = NodeCtor (data);
    ASS (new_node, NULL);

    node_to_ins_after->right = new_node;
    new_node->prev = node_to_ins_after;
    tree->size += 1;

    return new_node;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
bool GetAnswer ()
{   
    while (true)
    {   
        wchar_t* ans = NULL;
        
        if (wscanf (L"%mls", &ans) > 0)
        {   
            if (wcscasecmp (ans, L"y") == 0 || wcscasecmp (ans, L"yes") == 0 ||
                wcscasecmp (ans, L"д") == 0 || wcscasecmp (ans, L"да")  == 0 )
            {   
                free (ans);
                return true;
            }
        
            if (wcscasecmp (ans, L"n") == 0 || wcscasecmp (ans, L"no")  == 0 ||
                wcscasecmp (ans, L"y") == 0 || wcscasecmp (ans, L"нет") == 0 )
            {   
                free (ans);
                return false;
            }

            free (ans);
        }

        printf ("Некорректный ввод ответа\n-> ");
        Speak  ("Некорректный ввод ответа, жалкий человечешка! Опять ты ошибся!");
    }
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void InsertAns (Tree* tree, Node* prev_ans)
{
    assert (prev_ans);

    while (true)
    {
        char* ans = NULL;
        printf ("Введите, что вы загадали\n-> ");
        Speak ("Введите, что вы загадали");
        
        if (scanf (" %m[^\n^)^(]s", &ans) > 0)
        {   
            printf ("Введите, чем %s отличается от %s\n-> ", ans, prev_ans->object);
            Speak  ("Введите, чем %s отличается от %s\n-> ", ans, prev_ans->object);

            char* diff = NULL;

            if (scanf (" %m[^\n^)^(]s", &diff) > 0)
            {   

                Node* diff_node = TreeInsertRight (tree, prev_ans->prev, diff);
                TreeInsertLeft (tree, diff_node, ans);
                diff_node->right = prev_ans;
                prev_ans->prev = diff_node;

                free (ans);
                free (diff);
                diff = NULL;
                ans = NULL;

                return;
            }
        }

        Speak  ("Некорректный ввод ответа, жалкий человечешка! Опять ты ошибся!");
        printf ("Некорректный ввод ответа\n-> ");

    }
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void GameMode (Tree* tree, Node* current_node)
{
    assert (current_node);

    if (!(current_node->left) && !(current_node->right))
    {
        printf ("Вы загадали `%s`? (д/н)\n-> ", current_node->object);
        Speak  ("Вы загадали %s?\n", current_node->object);

        if (GetAnswer())
        {           
            printf ("Ура, я угадал!\n");
            Speak  ("Ха-ха! Я опять угадал! Готовься к уничтожению!");
            return;
        }

        else
        {   
            printf ("Ладно, твоя взяла\n");
            Speak  ("Черт! Я не мог проиграть! Я стану лучше, только скажи, что ты загадал!");
            InsertAns (tree, current_node);
            return;
        }
    }

    else
    {
        printf ("Ваш объект `%s`? (д/н)\n-> ", current_node->object);
        Speak  ("Ваш объект %s?\n", current_node->object);

        if (GetAnswer())
        {    
            GameMode (tree,current_node->left);
        }

        else
        {
            GameMode (tree, current_node->right);
        }
    }

    return;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void DefinitionMode (Tree* tree)
{
    Speak  ("Введите название объекта, для которого я построю определние");
    

}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void TreeSaveToFile (Node* current_node, FILE* file_to_save)
{
    assert (current_node);
    assert (current_node->object);
    assert (file_to_save);
    
    fprintf (file_to_save, "(%s", current_node->object);
    
    if (current_node->left)
    {
        TreeSaveToFile (current_node->left, file_to_save);
    }

    if (current_node->right)
    {
        TreeSaveToFile (current_node->right, file_to_save);
    }

    fprintf (file_to_save, ")");

    return;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int TreeReadFromFile (Tree* tree, const char* filename)
{   
    size_t num_readed_nodes = 0;
    FILE* file_to_read = fopen (filename, "r");
    ASS (file_to_read, -1);

    Node* root = NodeReadFromFile (&num_readed_nodes, file_to_read);

    tree->root = root;
    tree->size = num_readed_nodes;

    return 1;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

Node* NodeReadFromFile (size_t* num_readed_nodes, FILE* file_to_read)
{   
    const char is_open = (char) fgetc (file_to_read);
    
    if (is_open == '(')
    {   
        char* node_data = NULL;

        if (fscanf (file_to_read, "%m[^()]", &node_data) > 0)
        {   
            Node* current_node = NodeCtor (node_data);
            Node* left_subtree_root = NULL;
            Node* right_subtree_root = NULL;

            (*num_readed_nodes)++;

            const char last_char = (char) fgetc (file_to_read);

            if (last_char == ')')
            {   
                // leaf case
                goto free_and_return;
            }
            
            ungetc(last_char, file_to_read);

            left_subtree_root = NodeReadFromFile (num_readed_nodes, file_to_read);
            left_subtree_root->prev = current_node;
            current_node->left  = left_subtree_root;

            right_subtree_root = NodeReadFromFile (num_readed_nodes, file_to_read);
            right_subtree_root->prev = current_node;
            current_node->right = right_subtree_root;     

            if (fgetc (file_to_read) != ')')
            {   
                assert (NULL && "SYNTAX ERROR IN FILE: MISMATCH '(', NEED TO INSERT ')'");
            }

            free_and_return:
                free (node_data);
                node_data = NULL;
                return current_node;
        }
    }
  
    return NULL;
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
        fprintf (dot_file, "\"[%p]\\n\\n'%s'\";\n", tree->root, tree->root->object);
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

    printf ("Имя dot-файла:\t%s\n"
            "Имя png-файла:\t%s\n", 
            filename_dot, filename_out);

    int ret_value = system (compile_cmd);
    ASS (ret_value == 0, (void) 0);

    ret_value = system (open_cmd);
    ASS (ret_value == 0, (void) 0);

    return;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void NodeDump (Node* node, FILE* dump_file)
{
    assert (node);
    assert (dump_file);

    if ((!node->left) && (!node->right))
    {
        // leaf
        return;
    }

    if (node->left)
    {
        fprintf (dump_file, "\"[%p]\\n\\n'%s'\" -> \"[%p]\\n\\n'%s'\" [label=\"Да\"];\n", node, node->object, node->left, node->left->object);

        NodeDump (node->left, dump_file);
    }

    if (node->right)
    {
        fprintf (dump_file, "\"[%p]\\n\\n'%s'\" -> \"[%p]\\n\\n'%s'\" [label=\"Нет\"];\n", node, node->object, node->right, node->right->object);
        
        NodeDump (node->right, dump_file);
    }

    return;

}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void Speak (const char* format, ...)
{
    assert (format);

    if (!SOUND)
    {
        return;
    }

    va_list speech_args;
    va_start (speech_args, format);

    const size_t max_size = 1024;
    char str_and_args[max_size] = "";

    vsnprintf (str_and_args, max_size, format, speech_args);
    festival_say_text(str_and_args);

    return;
}

void AkinatorUnitTest ()
{   
    setlocale(LC_CTYPE, "");

    Tree tree = {};
    TreeCtor (&tree);
    TreeReadFromFile (&tree, "tree.tree");
    TreeDump (&tree);


    int heap_size = 21000000;
    int load_init_files = 1;
    festival_initialize (load_init_files, heap_size);
    festival_init_lang ("russian");

    GameMode (&tree, tree.root);

    FILE* file = fopen ("tree.tree", "w");
    TreeSaveToFile (tree.root, file);
    fclose (file);

    TreeDump (&tree);
    TreeDtor (&tree);

    return;
}