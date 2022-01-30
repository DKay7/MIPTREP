#include "hashset.h"
#include "libs/hashtable/default_hash_functions.h"

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

bool str_key_eq (const char* first, const char* second)
{
    return (strcmp (first, second) == 0);
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void data_printer (FILE* file, HT_Pair<const char*, dummy_t>* data_)
{   
    fprintf (file, "%s\n", data_->key);
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int main ()
{
    HashSet<const char*> set = {};

    HashSetCtor<const char*> (&set, 2, const_str_hash, str_key_eq);
    HashSetInsert (&set, "saboba");
    HashSetInsert (&set, "poshel");
    HashSetInsert (&set, "na");
    HashSetInsert (&set, "laby");
    HashSetInsert (&set, "abobas");
    printf ("CHECK SABOBA: %d; %lu\n", HashSetIn (&set, "saboba"), HashSetFind (&set, "saboba"));
    printf ("CHECK ABOBAS: %d; %lu\n", HashSetIn (&set, "abobas"), HashSetFind (&set, "abobas"));
    printf ("CHECK ABOBA:  %d; %lu\n", HashSetIn (&set, "aboba" ), HashSetFind (&set, "aboba" ));

    HashSetDump (&set, data_printer);

    printf ("CHECK SABOBA DELTING: %d;\n", HashSetDelete (&set, "saboba"));
    printf ("CHECK ABOBAS DELTING: %d;\n", HashSetDelete (&set, "abobas"));
    printf ("CHECK ABOBA  DELTING: %d;\n", HashSetDelete (&set, "aboba" ));

    HashSetDump (&set, data_printer);

    HashSetDtor (&set);

    return 0;
}