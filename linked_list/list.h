#include "math.h"
#include <stdio.h>

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
typedef struct 
{
    int mat;
    int kanava;
} data;

typedef data ll_type;

#define LL_DATA_POISON data {.mat = -1, .kanava = -1 }
#define NOT_EXISTS 0

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

#define CHECK_EMTY_NODES(list, ret)                     \
            if (list->empty_start == -1)                \
            {                                           \
                fprintf (stderr, "No empty nodes\n");   \
                LLDtor ((list));                        \
                return   ((ret));                       \
            } 
 
#define MOVE_EMPTY_PTR(list)                                    \
            list->empty_start = list->list[list->empty_start].next; \

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

typedef struct
{
    int prev;
    int next;
    int status = EMPTY;
    ll_type data;
} Node;

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

typedef struct 
{
    Node* list;
    int empty_start;
    int size;
    int errno;
    int sorted;
} LinkedList;

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int LLCtor (LinkedList* list, int size);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void LLDtor (LinkedList* list);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int LLInsertAfter (LinkedList* list, int addr, ll_type data);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int LLInsertBefore (LinkedList* list, int addr, ll_type data);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void LLDelete (LinkedList* list, int addr);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int LLDump (LinkedList* list, void (*DataPrinter)(FILE*, ll_type*));

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int LLSort (LinkedList* list);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int LLFindPhysicAdrres (LinkedList* list, int logical_adr);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
