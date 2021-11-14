#include "list.h"
#include <stdio.h>
#include <assert.h>
#include <malloc.h>
#include <stdlib.h>

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int LLCtor (LinkedList* ll, int size)
{
    assert (ll);
    assert (size > 0);

    ll->size = size;

    Node* tmp = (Node*) calloc ((size_t) size, sizeof (*tmp));

    if (!tmp)
    {
        ll->errno |= LL_MEM_ALLOC_ERROR;
        return ll->errno; 
    }

    ll->list = tmp;
    ll->empty_start = 1;
    ll->sorted = 1;
    ll->errno = LL_OK;

    ll->list[0].next = 0;
    ll->list[0].prev = 0;
    ll->list[0].status = EMPTY;
    ll->list[0].data = LL_DATA_POISON;

    for (int i = 1; i < ll->size; i++)
    {
        ll->list[i].next = (i + 1) % ll->size;
        ll->list[i].prev = -1;
        ll->list[i].status = EMPTY;
        ll->list[i].data = LL_DATA_POISON;
    }

    ll->list[ll->empty_start].prev = -1;
    ll->list[ll->size - 1].next = -1;


    return ll->errno;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void LLDtor (LinkedList* ll)
{
    free (ll->list);
    ll->list = NULL;
    ll->size = -1;
    ll->empty_start = -1;
    ll->sorted = -1;

    return;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int LLDump (LinkedList* ll)
{   
    assert (ll);

    char* filename_dot = tmpnam (NULL);
    char* filename_out = tmpnam (NULL);

    FILE* file = fopen (filename_dot, "w");

    if (file == NULL)
    {
        ll->errno |= CANT_OPEN_DUMP_FILE;
        return ll->errno;
    }

    fprintf (file,  "digraph { subgraph { rank=same \n");

    for (int i = 1; i < ll->size; i++)
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
                                <td> data: </td>
                                <td> %lf   </td>
                            </tr>
                            <tr>
                                <td port="prev"> prev: </td>
                                <td            > %d    </td>
                            </tr>
                            <tr>
                                <td port="next"> next: </td>
                                <td            > %d    </td>
                            </tr>                            
                        </table>
                    >
                ];

            )", i, (unsigned) ll->list[i].status, i, ll->list[i].data, ll->list[i].prev, ll->list[i].next);
    }

    for (int i = 1; i < ll->size; i++)
    {   
        if (ll->list[i].next > 0)
        {
            fprintf (file,  "\nnode_%02d:<next> -> node_%02d;\n", 
                    i, ll->list[i].next);
        }
        
        if (ll->list[i].prev > 0)
        {
            fprintf (file,  "\n node_%02d:<prev> -> node_%02d;\n", 
                    i, ll->list[i].prev);
        }
    }
    fprintf (file, "}\n");

    if (ll->list[0].next == 0 || ll->list[0].prev == 0)
    {
        fprintf (file, "node_00 [shape=rectangle, label=\"Terminating node\n(Node #0)\", style=\"filled\", fillcolor=grey];\n");
    }
    
    if (ll->empty_start <= 0)
    {
        fprintf (file, "node_empty_start [shape=rectangle, label=\"Terminating free elements node\n(Node #-1)\", style=\"filled\", fillcolor=grey];\n"
        "empty_start [shape=rectangle]; empty_start  -> node_empty_start;\n");
    }

    else
    {
        fprintf (file, "empty_start [shape=rectangle]; empty_start -> node_%02d;\n", ll->empty_start);
    }

    fprintf (file,  "head [shape=rectangle]; head -> node_%02d;\n"
                    "tail [shape=rectangle]; tail -> node_%02d;\n}",
            ll->list[0].next, ll->list[0].prev);

    fclose (file);

    char compile_cmd[2*L_tmpnam + 14];
    char open_cmd[L_tmpnam + 9];


    sprintf (compile_cmd, "dot -Tpng %s -o %s", filename_dot, filename_out);
    sprintf (open_cmd, "xdg-open %s", filename_out);

    system (compile_cmd);
    system (open_cmd);

    return ll->errno;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int LLInsertAfter (LinkedList* ll, int addr, ll_type data)
{
    assert (ll);
    assert (isnan (data));

    if (ll->list[addr].status == EMPTY)
    {
        addr = ll->list[0].prev;
    }

    CHECK_EMTY_NODES(ll, 0);
    
    int insert_to = ll->empty_start;
    
    MOVE_EMPTY_PTR (ll);

    ll->list[insert_to].prev    = addr;
    ll->list[insert_to].next    = ll->list[addr].next;

    ll->list[insert_to].data    = data;
    ll->list[insert_to].status  = NOT_EMPTY;
    ll->list[ll->list[addr].next].prev  = insert_to;
    ll->list[addr].next                 = insert_to;

    if (insert_to != addr + 1)
    {
        ll->sorted = 0;
    }

    return insert_to;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int LLInsertBefore (LinkedList* ll, int addr, ll_type data)
{
    assert (ll);
    assert (isnan (data));
    assert (addr >= 0);

    return LLInsertAfter (ll, ll->list[addr].prev, data);    
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void LLDelete (LinkedList* ll, int addr)
{
    assert (ll);
    assert (addr > 0);

    if (ll->list[addr].status == EMPTY)
    {
        return;
    }

    ll->list[ll->list[addr].prev].next = ll->list[addr].next;
    ll->list[ll->list[addr].next].prev = ll->list[addr].prev;

    ll->list[addr].data = LL_DATA_POISON;
    ll->list[addr].prev = NOT_EXISTS;
    ll->list[addr].next = ll->empty_start;
    ll->list[addr].status = EMPTY;
    ll->empty_start = addr;

    if (addr != ll->empty_start - 1)
    {
        ll->sorted = 0;
    }

    return;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int LLSort (LinkedList* ll)
{   

    assert (ll);

    Node* tmp_list = (Node*) calloc ((size_t) ll->size, sizeof(Node));

    if (!tmp_list)
    {
        ll->errno |= LL_MEM_ALLOC_ERROR;
        return ll->errno; 
    }
    
    int ll_ptr = 0;
    int i = 1;
    for (; i < ll->size; i++)
    {   
        ll_ptr = ll->list[ll_ptr].next;

        tmp_list[i]         = ll->list[ll_ptr];
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

    ll_ptr = ll->empty_start;
    ll->empty_start = i;

    for (; i < ll->size; i++)
    {   
        tmp_list[i]         = ll->list[ll_ptr];
        tmp_list[i].prev    = -1;
        tmp_list[i].next    = i + 1;

        ll_ptr = ll->list[ll_ptr].next;

        if (ll_ptr == -1)
        {
            break;
        }
    }
    
    tmp_list[i].next = -1;

    free (ll->list);
    ll->list = tmp_list;
    ll->sorted = 1;

    return ll->errno;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int LLFindPhysicAdrres (LinkedList* ll, int logical_adr)
{   
    assert (ll);
    assert (logical_adr > 0);
    
    if (ll->sorted)
    {
        return (logical_adr < ll->empty_start) ? logical_adr : 0;
    }

    int ll_ptr = 0;
    for (int i = 0; i < logical_adr; i++)
    {
        ll_ptr = ll->list[ll_ptr].next;
    }

    return ll_ptr;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void UnitTest ()
{
    LinkedList ll = {};
    LLCtor (&ll, 10);
    LLDump(&ll);

    LLInsertAfter(&ll, 0, 11);
    LLInsertAfter(&ll, 1, 12);

    LLInsertAfter(&ll, 2, 13);
    LLInsertAfter(&ll, 1, 14);
    LLInsertAfter(&ll, 1, 15);
    // LLInsertAfter(&ll, 1, 16);
    // LLInsertAfter(&ll, 1, 17);


    printf("%d\n", LLFindPhysicAdrres (&ll, 5));

    //LLDump(&ll);

    printf("%d\n", LLFindPhysicAdrres (&ll, 5));

    LLInsertAfter(&ll, 7, 18);
   // LLDump(&ll);

    LLSort(&ll);

    LLInsertAfter(&ll, 8, 19);
    LLInsertAfter(&ll, 8, 20);
    LLInsertAfter(&ll, 8, 21);
  
    //LLDump(&ll);
    printf("%d\n", LLFindPhysicAdrres (&ll, 5));


    LLDtor (&ll);

    return;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
