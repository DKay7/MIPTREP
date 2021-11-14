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

typedef double ll_type;

#define LL_DATA_POISON NAN
#define NOT_EXISTS 0
//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

#define CHECK_EMTY_NODES(ll, ret)                     \
            if (ll->empty_start == -1)                \
            {                                         \
                fprintf (stderr, "No empty nodes\n"); \
                LLDump ((ll));                        \
                LLDtor ((ll));                        \
                exit   ((ret));                       \
            } 
 
#define MOVE_EMPTY_PTR(ll)                                    \
            ll->empty_start = ll->list[ll->empty_start].next; \

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

int LLCtor (LinkedList* ll, int size);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void LLDtor (LinkedList* ll);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int LLInsertAfter (LinkedList* ll, int addr, ll_type data);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int LLInsertBefore (LinkedList* ll, int addr, ll_type data);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void LLDelete (LinkedList* ll, int addr);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int LLDump (LinkedList* ll);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int LLSort (LinkedList* ll);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int LLFindPhysicAdrres (LinkedList* ll, int logical_adr);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void UnitTest ();

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
