#include <inttypes.h>
#include "default_hash_funtions.h"

uint64_t int_hash(const int x)
{
    uint64_t hash = (uint64_t) x;
     
    hash = (hash ^ (hash >> 30)) * UINT64_C(0xbf58476d1ce4e5b9);
    hash = (hash ^ (hash >> 27)) * UINT64_C(0xbf58476d1ce4e5b9);
    hash = hash ^ (hash >> 31);

    return hash;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

// implementation of sdbm hash
uint64_t str_hash(char* str)
{
    uint64_t hash = (uint64_t) 'sdbm';
    int c;

    while ((c = *str++))
        hash = (uint64_t) c + (hash << 6) + (hash << 16) - hash;

    return hash;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

uint64_t char_hash(unsigned char x)
{
    return int_hash ((int) x);
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

