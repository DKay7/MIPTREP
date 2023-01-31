#include "disasm.h"
#include "../defines_and_setups/errors.h"

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int main (int argc, char** argv)
{   
    if (argc < 3)
    {   
        fprintf (stderr, "Not enough args\n");
        return -1;
    }

    AsmDecompiler adc = {};
    DisAsmCtor (&adc);
    DisAsmOpenFile (&adc, argv[1]);
    
    if (adc.errno != DISASM_OK)
    {
        DisAsmDump(&adc, stderr);
        DisAsmDtor (&adc);
        return -1;
    }

    DisAcmProcessFile (&adc, argv[2]);
    DisAsmDtor (&adc);

    return 0;
}
