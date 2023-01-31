#include "list.h"
#include <stdio.h>
#include <assert.h>
#include <malloc.h>
#include <stdlib.h>
#include <unistd.h>
#include "math.h"

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int LLCtor (LinkedList* list, int size)
{
    assert (list);
    assert (size > 0);

   list->size = size;

    Node* tmp = (Node*) calloc ((size_t) size, sizeof (*tmp));

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
    list->list[0].data = LL_DATA_POISON;

    for (int i = 1; i < list->size; i++)
    {
        list->list[i].next = (i + 1) % list->size;
        list->list[i].prev = -1;
        list->list[i].status = EMPTY;
        list->list[i].data = LL_DATA_POISON;
    }

    list->list[list->empty_start].prev = -1;
    list->list[list->size - 1].next = -1;


    return list->errno;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void LLDtor (LinkedList* list)
{
    free (list->list);
    list->list = NULL;
    list->size = -1;
    list->empty_start = -1;
    list->sorted = -1;

    return;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int LLDump (LinkedList* list, void (*DataPrinter)(FILE*, ll_type*))
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
            )", i, (unsigned) list->list[i].status, i);

        DataPrinter (file, &(list->list[i].data));
        
        fprintf(file, 
            R"( 
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

int LLInsertAfter (LinkedList* list, int addr,  ll_type ll_data)
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

int LLInsertBefore (LinkedList* list, int addr, ll_type ll_data)
{
    assert (list);
    assert (addr >= 0);

    return LLInsertAfter (list, list->list[addr].prev, ll_data);    
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void LLDelete (LinkedList* list, int addr)
{
    assert (list);
    assert (addr > 0);

    if (list->list[addr].status == EMPTY)
    {
        return;
    }

   list->list[list->list[addr].prev].next = list->list[addr].next;
   list->list[list->list[addr].next].prev = list->list[addr].prev;

   list->list[addr].data = LL_DATA_POISON;
   list->list[addr].prev = NOT_EXISTS;
   list->list[addr].next =list->empty_start;
   list->list[addr].status = EMPTY;
   list->empty_start = addr;

    if (addr != list->empty_start - 1)
    {
       list->sorted = 0;
    }

    return;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int LLSort (LinkedList* list)
{   

    assert (list);

    Node* tmp_list = (Node*) calloc ((size_t)list->size, sizeof(Node));

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
        tmp_list[i].prev    = -1;
        tmp_list[i].next    = i + 1;

       ll_ptr = list->list[ll_ptr].next;

        if (ll_ptr == -1)
        {
            break;
        }
    }
    
    tmp_list[i].next = -1;

    free (list->list);
    list->list = tmp_list;
    list->sorted = 1;

    return list->errno;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int LLFindPhysicAdrres (LinkedList* list, int logical_adr)
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
