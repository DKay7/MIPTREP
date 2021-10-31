#include "../text_lib/texlib.h"
#include "binlib.h"
#include <stdio.h>
#include <malloc.h>
#include <assert.h>

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void BinHeaderCtor (BinHeader* bh, int signature, double version)
{
    bh->signature = signature;
    bh->version = version;

    return;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int WriteToBinary (BinHeader* bh, unsigned char* data, int data_size, const char* filename)
{   
    assert (bh);
    assert (data);
    assert (filename);

    FILE* file = fopen (filename, "wb");
    CHECK_FILE_OPENED (file, "WriteToBinary", -1);

    fwrite (bh, sizeof (*bh), 1, file);
    fwrite (data, sizeof (unsigned char), data_size, file);

    CLOSE_FILE (file, "WriteToBinary", -1);

    return 0;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int ReadFromBinary (BinHeader* correct_bh, unsigned char** data, unsigned long* size, const char* filename)
{   
    assert (correct_bh);
    assert (filename);

    FILE* file = fopen (filename, "rb");
    CHECK_FILE_OPENED (file, "ReadFromBinary", -1);
   *size = CountSize (file);
    BinHeader actual_bh = {};
    fread (&actual_bh, 1, sizeof (actual_bh), file);

    if (!CheckHeader (correct_bh, actual_bh))
    {
        return -1;
    }

    *size = CountSize (file) - sizeof (BinHeader);
    *data = (unsigned char*) calloc (*size, sizeof (unsigned char));
    CHECK_POINTER (*data, "ReadFromBinary", -1);

    fread ((*data), sizeof (unsigned char), (*size), file);

    CLOSE_FILE (file, "ReadFromBinary", -1);

    return 0;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int CheckHeader (BinHeader* correct, BinHeader actual)
{
    return correct->signature == actual.signature && correct->version == actual.version;
}