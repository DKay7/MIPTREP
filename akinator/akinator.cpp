#include "akinator.h"
#include <assert.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#include <festival/festival.h>
#include <stdarg.h>
#include <wchar.h>
#include <stdio.h>
#include "libs/stack/stack.h"

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int SOUND = true;

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

Node* NodeCtor (const wchar_t* data)
{   
    assert (data);

    Node* node = (Node*) calloc (1, sizeof (*node));
    ASS (node != NULL, NULL);
    
    node->object = (wchar_t*) calloc (wcslen (data) + 1, sizeof (wchar_t));    
    ASS (node->object != NULL, NULL);

    wcscpy (node->object, data);
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

Node* TreeInsertRoot (Tree* tree, const wchar_t* data)
{
    assert (tree);
    
    Node* root = NodeCtor (data);
    ASS (root, NULL);
    tree->root = root;
    tree->size += 1;

    return root;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

Node* TreeInsertLeft (Tree* tree, Node* node_to_ins_after, const wchar_t* data)
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

Node* TreeInsertRight (Tree* tree, Node* node_to_ins_after, const wchar_t* data)
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
                wcscasecmp (ans, L"н") == 0 || wcscasecmp (ans, L"нет") == 0 )
            {   
                free (ans);
                return false;
            }
        }

        wprintf (L"Некорректный ввод ответа\n-> ");
        Speak ("Некорректный ввод ответа, жалкий человечешка! Опять ты ошибся!");
    }
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void InsertAns (Tree* tree, Node* prev_ans)
{
    assert (prev_ans);

    while (true)
    {
        wchar_t* ans = NULL;
        wprintf (L"Введите, что вы загадали\n-> ");
        
        if (wscanf (L" %ml[^\n()]s", &ans) > 0)
        {   
            wprintf (L"Введите, чем %ls отличается от %ls\n-> ", ans, prev_ans->object);

            wchar_t* diff = NULL;

            if (wscanf (L" %ml[^\n()]s", &diff) > 0)
            {   
               wprintf (L"ANS %ls\n", ans);

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

        wprintf (L"ANS: '%ls' Некорректный ввод ответа\n-> ", ans);
    }
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void GameMode (Tree* tree, Node* current_node)
{
    assert (current_node);

    if (!(current_node->left) && !(current_node->right))
    {
        wprintf (L"Вы загадали `%ls`? (д/н)\n-> ", current_node->object);
        Speak ("Вы загадали %ls?\n", current_node->object);

        if (GetAnswer())
        {           
            wprintf (L"Ура, я угадал!\n");
            Speak ("Ха-ха! Я опять угадал! Готовься к уничтожению!");
            return;
        }

        else
        {   
            wprintf (L"Ладно, твоя взяла\n");
            Speak ("Черт! Я не мог проиграть! Я стану лучше, только скажи, что ты загадал!");
            InsertAns (tree, current_node);
            return;
        }
    }

    else
    {
        wprintf (L"Ваш объект `%ls`? (д/н)\n-> ", current_node->object);
        freopen (NULL, "w", stdout);
        Speak ("Ваш объект %ls ", current_node->object);
        freopen (NULL, "w", stdout);

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

bool FindDefinitionForNode (Node* current_node, Stack* stack, const wchar_t* node_data_to_find)
{   
    assert (Stack);
    assert (current_node);
    assert (node_data_to_find);

    if (!(current_node->left) && !(current_node->right))
    {   
        if (wcscmp (current_node->object, node_data_to_find) == 0)
        {
            return true;
        }

        return false;
    }

    StackPush (stack, L"");
    StackPush (stack, current_node->object);

    if (FindDefinitionForNode (current_node->left, stack, node_data_to_find))
    {
        return true;
    }

    wchar_t* element = NULL;
    StackPop(stack, &element);
    StackPop(stack, &element);

    StackPush (stack, L"не");
    StackPush (stack, current_node->object);

    if (FindDefinitionForNode (current_node->right, stack, node_data_to_find))
    {
        return true;
    }
    
    element = NULL;
    StackPop(stack, &element);
    StackPop(stack, &element);

    return false;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void PrintStack (Stack* stack)
{
    assert (stack);
    
    size_t i = 0;
    for (; i < stack->size - 2; i += 2)
    {
        wprintf (L"->\t%ls\t%ls и\n", stack->data[i], stack->data[i + 1]);
        Speak ("%ls %ls", stack->data[i], stack->data[i + 1]);
    }

    wprintf (L"->\t%ls\t%ls\n", stack->data[i], stack->data[i + 1]);
    Speak ("%ls %ls", stack->data[i], stack->data[i + 1]);

    return;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void DefinitionMode (Tree* tree)
{   
    assert (tree);
    assert (tree->root);

    wprintf  (L"Введите название объекта, для которого я построю определние\n-> ");
    Speak ("Введите название объекта, для которого я построю определние");

    wchar_t* ans = NULL;
    ASS (wscanf (L" %ml[^\n]s", &ans) > 0, (void) 0);

    Stack stack = {};
    StackCtor (&stack, tree->size);
    bool is_successfull = FindDefinitionForNode (tree->root, &stack, ans);

    if (is_successfull)
    {
        PrintStack (&stack);
    }
    else
    {
        wprintf (L"Я не нашел такого объекта\n");
        Speak ("Я не нашел такого объекта");
    }

    StackDtor (&stack);
    free (ans);
    return;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void PrintDifferenceInPathes (Stack* first_path, const wchar_t* first_object, Stack* second_path, const wchar_t* second_object)
{
    assert (first_path);
    assert (second_path);

    if (wcscmp (first_object, second_object) == 0)
    {
        wprintf (L"Объекты одинаковые\n");
        Speak ("Дур очок они одинаковые");
        return;
    }

    wprintf (L"%ls и %ls похожи тем, что:\n", first_object, second_object);
    Speak ("%ls и %ls похожи тем, что", first_object, second_object);

    size_t min_size = (first_path->size < second_path->size) ?  first_path->size : second_path->size;
    size_t i = 0;

    for (; i < (min_size - 3); i += 2)
    {   
        if (wcscmp (first_path->data[i], second_path->data[i])         == 0 && 
            wcscmp (first_path->data[i + 1], second_path->data[i + 1]) == 0)
        {
            wprintf (L"->\t%ls\t%ls\n", first_path->data[i], first_path->data[i + 1]);
            Speak ("%ls %ls", first_path->data[i], first_path->data[i + 1]);
        }

        else
        {
            break;
        }
    }

    // TODO fix voice!!!
    // TODO fix last node case!!!
    
    wprintf (L"\nОбъекты отличаются тем, что:\n"
                L"-> %ls\t%ls\t%ls\n"
                L"-> %ls\t%ls\t%ls\n",
                first_object, first_path->data[i], first_path->data[i + 1], 
                second_object, second_path->data[i], second_path->data[i + 1]);

    Speak ("Объекты отличаются тем, что: %ls %ls %ls %ls %ls %ls",
            first_object,  first_path->data[i], first_path->data[i + 1], 
            second_object, second_path->data[i], second_path->data[i + 1]);

    return;
}

void DifferentiatorMode (Tree* tree)
{   
    assert (tree);
    assert (tree->root);

    wprintf  (L"Введите название первого объекта, разницу с которым мне искать\n-> ");
    Speak ("Введите название первого объекта, разницу с которым мне искать ");

    wchar_t* first_object = NULL;
    ASS (wscanf (L" %ml[^\n]s", &first_object) > 0, (void) 0);

    wprintf  (L"Введите название второго объекта, разницу с которым мне искать\n-> ");
    Speak ("Введите название второго объекта, разницу с которым мне искать");

    wchar_t* second_object = NULL;
    ASS (wscanf (L" %ml[^\n]s", &second_object) > 0, (void) 0);

    Stack first_path = {};
    Stack second_path = {};
    StackCtor (&first_path, tree->size);
    StackCtor (&second_path, tree->size);

    bool is_first_successfull = FindDefinitionForNode (tree->root, &first_path, first_object);
    bool is_second_successfull = FindDefinitionForNode (tree->root, &second_path, second_object);

    if (is_first_successfull && is_second_successfull)
    {
        PrintDifferenceInPathes (&first_path, first_object, &second_path, second_object);
    }

    else if (is_first_successfull)
    {
        wprintf (L"Я не нашел объекта %ls\n", second_object);
        Speak ("Я не нашел объекта %ls", second_object);
    }

    else if (is_second_successfull)
    {
        wprintf (L"Я не нашел объекта %ls\n", first_object);
        Speak ("Я не нашел объекта %ls", first_object);
    }

    else
    {
        wprintf (L"Я не нашел ни одного из этих объектов\n");
        Speak ("Я не нашел ни одного из этих объектов");
    }

    StackDtor (&first_path);
    StackDtor (&second_path);
    free (first_object);
    free (second_object);

    return;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void TreeSaveToFile (Node* current_node, FILE* file_to_save)
{
    assert (current_node);
    assert (current_node->object);
    assert (file_to_save);
    
    fprintf (file_to_save, "(%ls", current_node->object);
    
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
        wchar_t* node_data = NULL;

        if (fscanf (file_to_read, "%ml[^()]", &node_data) > 0)
        {   
            Node* current_node = NodeCtor (node_data);
            Node* left_subtree_root  = NULL;
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
    fprintf (dot_file,  "digraph {\n rankdir = HR;\n node[shape=box, style=rounded]\n");

    if (tree->root)
    {   
        fprintf (dot_file, "\"[%p]\\n\\n'%ls'\";\n", tree->root, tree->root->object);
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

    wprintf (L"Имя dot-файла:\t%s\n"
             L"Имя png-файла:\t%s\n", 
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
        fprintf (dump_file, "\"[%p]\\n\\n'%ls'\" -> \"[%p]\\n\\n'%ls'\" [label=\"Да\"];\n", node, node->object, node->left, node->left->object);

        NodeDump (node->left, dump_file);
    }

    if (node->right)
    {
        fprintf (dump_file, "\"[%p]\\n\\n'%ls'\" -> \"[%p]\\n\\n'%ls'\" [label=\"Нет\"];\n", node, node->object, node->right, node->right->object);
        
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

    va_list speech_args_for_size;
    va_list speech_args;
    va_start (speech_args_for_size, format);
    va_copy (speech_args, speech_args_for_size);

    int total_str_size = vsnprintf (NULL, 0, format, speech_args_for_size) + 1;
    ASS (total_str_size >= 0, (void) 0);

    char* str_and_args = (char*) calloc ((size_t) total_str_size, sizeof (*str_and_args));
    ASS (str_and_args, (void) 0);

    vsnprintf (str_and_args, (size_t) total_str_size, format, speech_args);

    festival_say_text(str_and_args);
    
    free (str_and_args);
    va_end (speech_args);
    va_end (speech_args_for_size);

    return;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void AkinatorUnitTest ()
{   
    setlocale(LC_CTYPE, "");
    setvbuf (stdout, NULL, _IONBF, 0);

    Tree tree = {};
    TreeCtor (&tree);
    TreeReadFromFile (&tree, "tree.tree");
    TreeDump (&tree);


    int heap_size = 21000000;
    int load_init_files = 1;
    festival_initialize (load_init_files, heap_size);
    festival_init_lang ("russian");

    // DefinitionMode (&tree);
    //GameMode (&tree, tree.root);
    DifferentiatorMode (&tree);

    FILE* file = fopen ("tree.tree", "w");
    TreeSaveToFile (tree.root, file);
    fclose (file);

    TreeDump (&tree);
    TreeDtor (&tree);

    return;
}