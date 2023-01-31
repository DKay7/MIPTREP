#include <malloc.h>

typedef int Data;

struct Node {
    Data val;
    struct Node *next;
};

struct List {
    struct Node *head;
};

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

struct List *list_create()
{
    struct List *l = (struct List *) calloc(1, sizeof(*l));
    l->head = NULL;

    return l;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void list_add_first(struct List *list, Data x)
{
    struct Node *new_node = (struct Node *) calloc(1, sizeof(*new_node));

    new_node->val = x;
    new_node->next = NULL;

    new_node->next = list->head;
    list->head = new_node;
}

void list_add_last(struct List *list, Data x)
{
    struct Node *new_node = (struct Node *) calloc(1, sizeof(*new_node));

    new_node->val = x;
    new_node->next = NULL;

    struct Node *cur_node = list->head;
    
    while (cur_node->next)
        cur_node = cur_node->next;

    cur_node->next = new_node;
}

Data list_remove_first(struct List *list)
{
    struct Node *to_remove = list->head;
    list->head = list->head->next;

    Data data_to_return = to_remove->val;
    free(to_remove);

    return data_to_return;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

Data list_remove_last(struct List *list)
{   
    struct Node *cur_node = list->head,
                *data = list->head;

    if (cur_node->next == NULL) {
        list->head = NULL;
    } else {
        while (cur_node->next->next != NULL) {
            cur_node = cur_node->next;
        }

        data = cur_node->next;
        cur_node->next = NULL;
    }
    
    Data data_to_return = data->val;
    free(data), data = NULL;

    return data_to_return;

}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

Data list_get_first (struct List * list)
{
    return list->head->val;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

Data list_get_last (struct List * list)
{   
    struct Node *cur_node = list->head;

    while (cur_node->next) {
        cur_node = cur_node->next;
    }

    return cur_node->val;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void list_print (struct List * list)
{
    if (list == NULL || list->head == NULL)
    {
        printf ("Empty list\n");
        return;
    }

    struct Node *cur_node = list->head;
  
    while (cur_node) {
        printf ("%d ", cur_node->val);
        cur_node = cur_node->next;
    }

    printf ("\n");

    return;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int list_size(struct List * list)
{
    int size = 0;

    struct Node *cur_node = list->head;

    while (cur_node) {
        size += 1;
        cur_node = cur_node->next;
    }

    return size;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void list_clear(struct List * list)
{   
    if (!list)
    {
        return;
    }

    struct Node *cur_node = list->head;
    struct Node *prev_node = list->head;

    while (cur_node) {
        prev_node = cur_node;
        cur_node = prev_node->next;

        prev_node->next = NULL;
        prev_node->val = -1;
        free (prev_node);
        prev_node = NULL;
    }

    free (cur_node);
    list->head = NULL;

    return;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void list_destroy (struct List * list)
{   
    list_clear(list);
    free (list);
    list = NULL;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int main ()
{   
    struct List * list = list_create();
    // list_destroy (list);
    list_add_first(list, 5);
    // // printf ("LIST %d\n", list->head->val);

    // list_add_first(list, 7);
    // list_add_last(list, 8);
    // list_add_last(list, 9);
    // list_add_last(list, 11);
    // list_add_last(list, 12);
    // list_add_last(list, 13);

    #include <stdio.h>
    printf ("SIZE %d\n", list_size (list));
    list_print(list);
    
    // printf ("\n");
    // // list_clear (list);
    // // list_print(list);

    // printf ("DATA FIRST %d\n", list_remove_first (list));
    // printf ("SIZE %d\n", list_size (list));
    // list_print(list);
    
    // printf ("\n");
    
    // printf ("DATA LAST %d\n", list_remove_last (list));
    // printf ("SIZE %d\n", list_size (list));
    // list_print(list);
    
    // printf ("\n");
    
    // printf ("DATA FIRST %d\n", list_get_first (list));
    // printf ("SIZE %d\n", list_size (list));
    // list_print(list);
    
    // printf ("\n");

    // printf ("DATA LAST %d\n", list_get_last (list));
    // printf ("SIZE %d\n", list_size (list));
    // list_print(list);

    // printf ("\n");
    // list_clear (list);
    
    // list_add_first(list, 17);
    // list_add_last(list, 18);
    // list_add_last(list, 19);
    // list_add_last(list, 111);
    // list_add_last(list, 112);
    // list_add_last(list, 113);

    //  printf ("SIZE %d\n", list_size (list));
    // list_print(list);
    
    // printf ("\n");

    // printf ("DATA FIRST %d\n", list_remove_first (list));
    // printf ("SIZE %d\n", list_size (list));
    // list_print(list);
    
    printf ("\n");
    
    printf ("DATA LAST %d\n", list_remove_last (list));
    printf ("SIZE %d\n", list_size (list));
    list_print(list);
    
    // printf ("\n");
    
    // printf ("DATA FIRST %d\n", list_get_first (list));
    // printf ("SIZE %d\n", list_size (list));
    // list_print(list);
    
    // printf ("\n");

    // printf ("DATA LAST %d\n", list_get_last (list));
    // printf ("SIZE %d\n", list_size (list));
    // list_print(list);

    // printf ("\n");

    list_destroy(list);

    return 0;
}
