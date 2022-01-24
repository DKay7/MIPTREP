#pragma once

#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <malloc.h>
#include <stdlib.h>
#include <unistd.h>
#include "math.h"


//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

enum LL_ERRORS
{
    LL_OK                                       = 0x01,
    LL_MEM_ALLOC_ERROR                          = 0x02,
    LL_INSERT_TO_EXISTING_VERTEX_AS_TO_EMTPY    = 0x04,
    CANT_OPEN_DUMP_FILE                         = 0x08,
};

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

enum NODE_STATUSES
{
    EMPTY           = 0x61DBAD,
    NOT_EMPTY       = 0x74D073,
    ERROR           = 0xFE0000,
};

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

#define POISON 0xDEDF
#define NOT_EXISTS 0
#define NOT_EXISTS_EMPTY -1

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

#define CHECK_EMTY_NODES(list, ret)                     \
            if (list->empty_start == NOT_EXISTS_EMPTY)                \
            {                                           \
                fprintf (stderr, "No empty nodes\n");   \
                LLDtor ((list));                        \
                return   ((ret));                       \
            } 
 
#define MOVE_EMPTY_PTR(list)                                        \
            list->empty_start = list->list[list->empty_start].next; \

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

template <typename T>
struct Node
{
    int prev;
    int next;
    int status = EMPTY;
    T data;
};

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

template <typename T>
struct LinkedList
{
    Node<T>* list;
    int empty_start;
    int size;
    int errno;
    int sorted;
};

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

template <typename T>
void PoisonData (T* data_ptr, size_t size)
{   
    assert (data_ptr);
    memset ((void*) data_ptr, POISON, size);
    
    return;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

template <typename T>
int LLCtor (LinkedList<T>* list, int size)
{
    assert (list);
    assert (size > 0);

    list->size = size;

    Node<T>* tmp = (Node<T>*) calloc ((size_t) size, sizeof (*tmp));

    if (!tmp)
    {
        list->errno |= LL_MEM_ALLOC_ERROR;
        return list->errno; 
    }

    list->list = tmp;
    list->empty_start = 1;
    list->sorted = 1;
    list->errno = LL_OK;

    list->list[0].next = 0;
    list->list[0].prev = 0;
    list->list[0].status = EMPTY;

    PoisonData<T> (&(list->list[0].data), sizeof (list->list[0].data));

    for (int i = 1; i < list->size; i++)
    {
        list->list[i].next = (i + 1) % list->size;
        list->list[i].prev = NOT_EXISTS_EMPTY;
        list->list[i].status = EMPTY;
        PoisonData<T> (&(list->list[i].data), sizeof (list->list[i].data));
    }

    list->list[list->empty_start].prev = NOT_EXISTS_EMPTY;
    list->list[list->size - 1].next = NOT_EXISTS_EMPTY;

    return list->errno;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

template <typename T>
void LLDtor (LinkedList<T>* list)
{
    free (list->list);
    list->list = NULL;
    list->size = -1;
    list->empty_start = -1;
    list->sorted = -1;

    return;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

template <typename T>
int LLDump (LinkedList<T>* list, void (*DataPrinter)(FILE*, T*))
{   
    assert (list);

    char filename_dot[] = "/tmp/fileXXXXXX";
    char filename_out[] = "/tmp/fileXXXXXX";

    int dot_fd = mkstemp (filename_dot);
    close (mkstemp (filename_out));

    FILE* file = fdopen (dot_fd, "w");
    
    if (file == NULL)
    {
        list->errno |= CANT_OPEN_DUMP_FILE;
        return list->errno;
    }

    fprintf (file,  "digraph { subgraph { rank=same \n");

    for (int i = 1; i < list->size; i++)
    {   
        fprintf (file, 
            R"(
                node_%02d 
                [   
                    style="filled",
                    fillcolor="#%X"
                    shape=plaintext, 
                    label=
                    <
                    <table border="0" cellborder="1" cellspacing="0">
                    <tr>
                    <td colspan="2">Node #%d</td>
                    </tr>
                    <tr>
                    <td colspan="2">
            )", i, (unsigned) list->list[i].status, i);

        DataPrinter (file, &(list->list[i].data));
        
        fprintf(file, 
            R"( 
                </td>
                </tr>
                <tr>
                <td port="prev_out" > prev: </td>
                <td port="prev_in" > %d    </td>
                </tr>
                <tr>
                <td port="next_in" > next: </td>
                <td port="next_out"> %d    </td>
                </tr>                            
                </table>
                >
                ];
            )", list->list[i].prev, list->list[i].next);
    }

    for (int i = 1; i < list->size; i++)
    {   
        if (list->list[i].next > 0)
        {
            fprintf (file,  "\nnode_%02d:<next_out> -> node_%02d:<next_in>;\n", 
                    i, list->list[i].next);
        }
        
        if (list->list[i].prev > 0)
        {
            fprintf (file,  "\n node_%02d:<prev_out> -> node_%02d:<prev_in>;\n", 
                    i, list->list[i].prev);
        }
    }
    fprintf (file, "}\n");

    if (list->list[0].next == 0 || list->list[0].prev == 0)
    {
        fprintf (file, "node_00 [shape=rectangle, label=\"Terminating node\n(Node #0)\", style=\"filled\", fillcolor=grey];\n");
    }
    
    if (list->empty_start <= 0)
    {
        fprintf (file, "node_empty_start [shape=rectangle, label=\"Terminating free elements node\n(Node #-1)\", style=\"filled\", fillcolor=grey];\n"
        "empty_start [shape=rectangle]; empty_start  -> node_empty_start;\n");
    }

    else
    {
        fprintf (file, "empty_start [shape=rectangle]; empty_start -> node_%02d;\n", list->empty_start);
    }

    fprintf (file,  "head [shape=rectangle]; head -> node_%02d;\n"
                    "tail [shape=rectangle]; tail -> node_%02d;\n}",
           list->list[0].next, list->list[0].prev);

    fclose (file);

    char compile_cmd[2*16 + 14];
    char open_cmd[16 + 9];

    sprintf (compile_cmd, "dot -Tpng %s -o %s", filename_dot, filename_out);
    sprintf (open_cmd, "xdg-open %s", filename_out);

    system (compile_cmd);
    system (open_cmd);

    return list->errno;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

template <typename T>
int LLInsertAfter (LinkedList<T>* list, int addr,  T ll_data)
{
    assert (list);

    if (list->list[addr].status == EMPTY)
    {
        addr = list->list[0].prev;
    }

    CHECK_EMTY_NODES(list, 0);
    
    int insert_to = list->empty_start;
    
    MOVE_EMPTY_PTR (list);

    list->list[insert_to].prev    = addr;
    list->list[insert_to].next    = list->list[addr].next;
    list->list[insert_to].data    = ll_data;
    list->list[insert_to].status  = NOT_EMPTY;

    list->list[list->list[addr].next].prev   = insert_to;
    list->list[addr].next                    = insert_to;

    if (insert_to != addr + 1)
    {
       list->sorted = 0;
    }

    return insert_to;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

template <typename T>
int LLInsertBefore (LinkedList<T>* list, int addr, T ll_data)
{
    assert (list);
    assert (addr >= 0);

    return LLInsertAfter (list, list->list[addr].prev, ll_data);    
}


//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

template <typename T>
void LLDelete (LinkedList<T>* list, int addr)
{
    assert (list);
    assert (addr > 0);

    if (list->list[addr].status == EMPTY)
    {   
        return;
    }

    list->list[list->list[addr].prev].next = list->list[addr].next;
    list->list[list->list[addr].next].prev = list->list[addr].prev;

    PoisonData<T> (&(list->list[addr].data), sizeof (list->list[addr].data));

    list->list[addr].prev = NOT_EXISTS;
    list->list[addr].next = list->empty_start;
    list->list[addr].status = EMPTY;
    list->empty_start = addr;

    if (addr != list->empty_start - 1)
    {
       list->sorted = 0;
    }

    return;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

template <typename T>
int LLSort (LinkedList<T>* list)
{   

    assert (list);

    Node<T>* tmp_list = (Node<T>*) calloc ((size_t) list->size, sizeof(*tmp_list));

    if (!tmp_list)
    {
       list->errno |= LL_MEM_ALLOC_ERROR;
        return list->errno; 
    }
    
    int ll_ptr = 0;
    int i = 1;
    for (; i < list->size; i++)
    {   
       ll_ptr = list->list[ll_ptr].next;

        tmp_list[i]         = list->list[ll_ptr];
        tmp_list[i].prev    = i - 1;
        tmp_list[i].next    = i + 1;

        if (ll_ptr == 0)
        {   
            break;
        }
    }

    tmp_list[i - 1].next = 0;
    tmp_list[0].next = 1;
    tmp_list[0].prev = i - 1;

    ll_ptr = list->empty_start;
    list->empty_start = i;

    for (; i < list->size; i++)
    {   
        tmp_list[i]         = list->list[ll_ptr];
        tmp_list[i].prev    = NOT_EXISTS_EMPTY;
        tmp_list[i].next    = i + 1;

        ll_ptr = list->list[ll_ptr].next;

        if (ll_ptr == NOT_EXISTS_EMPTY)
        {
            break;
        }
    }
    
    tmp_list[i].next = NOT_EXISTS_EMPTY;

    free (list->list);
    list->list = tmp_list;
    list->sorted = 1;

    return list->errno;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

template <typename T>
int LLFindPhysicAdrres (LinkedList<T>* list, int logical_adr)
{   
    assert (list);
    assert (logical_adr > 0);
    
    if (list->sorted)
    {
        return (logical_adr < list->empty_start) ? logical_adr : 0;
    }

    int ll_ptr = 0;
    for (int i = 0; i < logical_adr; i++)
    {
        ll_ptr = list->list[ll_ptr].next;
    }

    return ll_ptr;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
