#include <malloc.h>

typedef int Data;

struct Node {
	struct Node * next;
	struct Node * prev;
	Data data;
};

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void list_init(struct Node * list)
{   
    list->next = list;
    list->prev = list;
    list->data = {}; 

    return;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void list_insert(struct Node* list, struct Node* t)
{
    Node* tmp = list->next;
    
    list->next = t;
    t->prev = list;

    t->next = tmp;
    tmp->prev = t;

    return;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void list_insert_before(struct Node * list, struct Node * t)
{
    Node* tmp = list->prev;
    list->prev = t;
    t->next = list;

    t->next = tmp;
    tmp->prev = t;

    return;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void list_remove(struct Node * t)
{   

    t->next->prev = t->prev;
    t->prev->next = t->next;

    t->next = NULL;
    t->prev = NULL;
    free (t);
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

struct Node * list_push_front(struct Node * list, Data d)
{
    Node* new_element = (Node*) calloc (1, sizeof (*new_element));
    new_element->data = d;

    list_insert_before (list, new_element);

    return list;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

struct Node * list_push_back(struct Node * list, Data d)
{
    Node* new_element = (Node*) calloc (1, sizeof (*new_element));
    new_element->data = d;

    list_insert (list, new_element);

    return list;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

Data list_pop_front(struct Node * list)
{   
    Data d = list->data;
    list_remove(list);

    return d;
}   

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

Data list_pop_back(struct Node * list)
{
    Data d = list->prev->data;
    list_remove(list);
 
    return d;
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
