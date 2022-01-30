#pragma once
#include "libs/hashtable/hashtable.h"
#include <inttypes.h>
#include <malloc.h>

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

#define INCORRECT_FIND_OUTPUT ((uint64_t) (hash_set->hash_table->values->size + 1))

#define ASS(cond, ret)                                                  \
    if(!(cond))                                                         \
    {                                                                   \
        fprintf (stderr, "Soft assertation ( " #cond " ) has failed "   \
                         "in file %s:%d \n", __FILE__, __LINE__);       \
        return ret;                                                     \
    }

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

typedef struct {} dummy_t;

template <typename K>
struct HashSet
{
    HashTable<K, dummy_t>* hash_table;
};

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

template <typename K>
void HashSetCtor (HashSet<K>* hash_set,
                  uint64_t size, 
                  uint64_t (*HashFunction)(K), 
                  bool (*KeyEqualityFunc)(K, K) = SimpleKeyEqualityFunction)
{
    assert (hash_set);
    assert (HashFunction);
    assert (KeyEqualityFunc);

    ASS (size > 1 && "size should be bigger than 1", (void) 0);

    HashTable<K, dummy_t>* hash_table = (HashTable<K, dummy_t>*) calloc (1, sizeof (*hash_table));
    HashTableCtor (hash_table, size, HashFunction, KeyEqualityFunc);
    hash_set->hash_table = hash_table;

    return;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

template <typename K>
void HashSetDtor (HashSet<K>* hash_set)
{   
    assert (hash_set);

    HashTableDtor (hash_set->hash_table);
    free (hash_set->hash_table);
    hash_set->hash_table = NULL;

    return;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

template <typename K>
bool HashSetInsert (HashSet<K>* hash_set, K key)
{
    assert (hash_set);

    return HashTableInsert (hash_set->hash_table, key, (dummy_t) {});
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

template <typename K>
bool HashSetDelete (HashSet<K>* hash_set, K key)
{
    assert (hash_set);
    
    return HashTableDelete (hash_set->hash_table, key);
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

template <typename K>
bool HashSetIn (HashSet<K>* hash_set, K key)
{   
    assert (hash_set);

    uint64_t position = __HashTableSearchForKey (hash_set->hash_table, key);
    
    return position != INCORRECT_FIND_OUTPUT;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

template <typename K>
uint64_t HashSetFind (HashSet<K>* hash_set, K key)
{   
    assert (hash_set);
    uint64_t position = __HashTableSearchForKey (hash_set->hash_table, key);
    // TODO do we really need next line? maybe we should find another way
    ASS (position != INCORRECT_FIND_OUTPUT && "element not in hash set!", INCORRECT_FIND_OUTPUT);
    
    return position;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

template <typename K>
void HashSetDump (HashSet<K>* hash_set, void (*DataPrinter)(FILE*, HT_Pair<K, dummy_t>*))
{
    assert (hash_set);
    assert (DataPrinter);

    HashTableDump (hash_set->hash_table, DataPrinter);

    return;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

#undef ASS
#undef INCORRECT_FIND_OUTPUT
