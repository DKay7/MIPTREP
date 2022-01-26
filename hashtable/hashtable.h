#include "libs/linked_list_templates/list.h"
#include <assert.h>
#include <malloc.h>


//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

#define ASS(cond, ret)                                                  \
    if(!(cond))                                                         \
    {                                                                   \
        fprintf (stderr, "Soft assertation ( " #cond " ) has failed "   \
                         "in file %s:%d \n", __FILE__, __LINE__);       \
        return ret;                                                     \
    }

#define POISON 0xDEDF

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

enum HASHNODE_STATUSES 
{
    NODE_EMPTY       = 0xBEEF,
    NODE_NOT_EMPTY   = 0xBACA, 
};

struct HashNode
{
    int start_index;
    int len;
    HASHNODE_STATUSES status;
};

template <typename T>
struct HashTable
{
    HashNode*  indexes;
    LinkedList<T>* list;    
    int (*HashFunction)(HashTable<T>* hash_table, T* pointer);
    int size;
};

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

template <typename T>
int DefaultHashFunction (HashTable<T>* hash_table, T* pointer)
{
    assert(pointer);
    assert (hash_table);
    assert (hash_table->size > 0);

    ssize_t hash =  (1000 - 7) + 'meow';
    unsigned char* ptr = (unsigned char*) pointer;

    for (size_t i = 0; i < sizeof (*ptr); i++)
    {
        hash += *(ptr + i);
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }

    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);

    return (int) hash % hash_table->size;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

template <typename T>
void HashTableCtor (HashTable<T>* hash_table, int table_size, int  (*HashFunction)(HashTable<T>*, T*))
{
    assert (hash_table);
    assert (table_size > 0);

    hash_table->HashFunction = HashFunction;
    hash_table->size = table_size;
    hash_table->indexes = (HashNode*) calloc ((size_t) table_size, sizeof (*hash_table->indexes));
    ASS (hash_table->indexes, (void) 0);

    memset (hash_table->indexes, POISON, (size_t) table_size * sizeof (*hash_table->indexes));
    for (int i = 0; i < table_size; i++)
        hash_table->indexes[i].status = NODE_EMPTY;

    LinkedList<T>* list = (LinkedList<T>*) calloc (1, sizeof (*list));
    ASS (list, (void) 0);

    LLCtor (list, table_size);

    hash_table->list = list;

    return;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

template <typename T>
void HashTableDtor (HashTable<T>* hash_table)
{
    assert (hash_table);

    LLDtor (hash_table->list);
    free (hash_table->list);
    free (hash_table->indexes);
    hash_table->size = 0;
    hash_table->indexes = NULL;

    return;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

template <typename T>
int HashTableInsert (HashTable<T>* hash_table, T element)
{
    assert (hash_table);

    int position = hash_table->HashFunction (hash_table, &element);

    if (hash_table->indexes[position].status == NODE_EMPTY)
    {   
        // just insert
        printf ("EMPTY\n\n");
        int list_position = LLInsertAfter (hash_table->list, hash_table->list->list[0].prev, element);
        hash_table->indexes[position] = { .start_index = (int)list_position, .len = 1, .status = NODE_NOT_EMPTY };

        return list_position;
    }

    else 
    {
        // check size and go through list
        int block_size = hash_table->indexes[position].len;
        int index_to_insert_after = hash_table->indexes[position].start_index;

        for (int i = 0; i < block_size - 1; i++)
        {
            index_to_insert_after = hash_table->list->list[index_to_insert_after].next;
        }

        int list_position = LLInsertAfter (hash_table->list, index_to_insert_after, element);
        hash_table->indexes[position].len += 1;

        return list_position;
    }
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

template <typename T>
bool HashTableDelete (HashTable<T>* hash_table, T element)
{
    assert (hash_table);

    int position = hash_table->HashFunction (hash_table, &element);
    ssize_t list_position = HashTableFind (hash_table, element);
    ASS (list_position > 0, false);

    // case if we delete element  which hash table's element points at
    if (list_position == hash_table->indexes[position].start_index)
    {
        if (hash_table->indexes[position].len == 1)
        {
            LLDelete (hash_table->list, list_position);
            
            memset (&hash_table->indexes[position], POISON, sizeof (hash_table->indexes[position]));
            hash_table->indexes[position].len = 0;
            hash_table->indexes[position].status = NODE_EMPTY;
            return true;
        }

        else
        {
            int next_index = hash_table->list->list[list_position].next;
            LLDelete (hash_table->list, list_position);
            hash_table->indexes[position].len -= 1;
            hash_table->indexes[position].start_index = next_index;
            return true;
        }
    }

    LLDelete (hash_table->list, list_position);
    hash_table->indexes[position].len -= 1;
    return true;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

template <typename T>
int HashTableFind (HashTable<T>* hash_table, T element)
{
    assert (hash_table);

    int position = hash_table->HashFunction (hash_table, &element);
    ASS (hash_table->indexes[position].status != NODE_EMPTY, -1);

    int block_size = hash_table->indexes[position].len;
    int list_position = hash_table->indexes[position].start_index;

    for (int i = 0; i < block_size - 1; i++)
    {   
        list_position = hash_table->list->list[list_position]->next;
        if (hash_table->list->list[list_position].data == element)
            break;
    }

    return list_position;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

template <typename T>
void HashTableDump (HashTable<T>* hash_table, void (*DataPrinter)(FILE*, T*))
{
    assert (list);

    char filename_dot[] = "/tmp/fileXXXXXX";
    char filename_out[] = "/tmp/fileXXXXXX";

    int dot_fd = mkstemp (filename_dot);
    close (mkstemp (filename_out));

    FILE* file = fdopen (dot_fd, "w");
    ASS (file, (void) 0);

    fprintf (file,  "digraph { \n");
    __LLDrowSubgraph (file, hash_table->list, DataPrinter);
    __HashTableDrowSubgraph (file, hash_table);

    fprintf (file, "}\n");

    fclose (file);

    char compile_cmd[2*16 + 14];
    char open_cmd[16 + 9];

    sprintf (compile_cmd, "dot -Tpng %s -o %s", filename_dot, filename_out);
    sprintf (open_cmd, "xdg-open %s", filename_out);

    printf ("COMPILING %s\n", compile_cmd);

    system (compile_cmd);
    system (open_cmd);

    return;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

template <typename T>
void __HashTableDrowSubgraph (FILE* file, HashTable<T>* hash_table)
{   
    fprintf (file, "subgraph { ");

    fprintf (file, 
            R"(
                hs_main_node 
                [   
                    style="filled",
                    shape=plaintext, 
                    label=
                    <
                    <table border="1" cellborder="1" cellspacing="0">
                    <tr>)");

    for (int i = 0; i < hash_table->size; i++)
    {
        fprintf (file,
                R"(
                    <td>
                    <table border="0" cellborder="1" cellspacing="0"  port="hs_node_%02d">
                    <tr>
                    <td colspan="2">Node #%d</td>
                    </tr>
                    <tr>
                    <td>STORED INDEX</td>
                    <td>%d</td>
                    </tr>
                    <tr>
                    <td>STATUS</td>
                    <td>%s</td>
                    </tr>
                    <tr>
                    <td>LEN</td>
                    <td>%d</td>
                    </tr>
                    </table>
                    </td>
                )", i, i, hash_table->indexes[i].start_index, 
                (hash_table->indexes[i].status == NODE_EMPTY)? "EMPTY":"NOT EMPTY",
                hash_table->indexes[i].len);
    }

    fprintf (file, 
            R"( 
                </tr>
                </table>
                >
                ];
            )");

    for (int i = 0; i < hash_table->size; i++)
    {
        if (hash_table->indexes[i].status != NODE_EMPTY)
            fprintf (file, "hs_main_node:<hs_node_%02d> -> node_%02d:<>;\n", i, hash_table->indexes[i].start_index);
    }

    fprintf (file, "}\n");
}