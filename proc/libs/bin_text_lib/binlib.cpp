#include <stdio.h>
#include "../text_lib/texlib.h"
#include "binlib.h"

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

    FILE* file = fopen (filename, "wb");
    CHECK_FILE_OPENED (file, "WriteToBinary", -1);

    fwrite (bh, sizeof (*bh), 1, file);
    fwrite (data, sizeof (unsigned char), data_size, file);

    CLOSE_FILE (file, "WriteToBinary", -1);

    return 0;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int ReadFromBinary (unsigned char* data, const char* filename)
{   
    return 0;
}