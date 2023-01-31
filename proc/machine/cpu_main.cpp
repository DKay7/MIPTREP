#include "cpu.h"

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int main (int argc, char** argv)
{   
    if (argc < 2)
    {   
        fprintf (stderr, "Not enough args\n");
        return -1;
    }

    Cpu cpu = {};
    CpuCtor (&cpu);
    CpuOpenFile (&cpu, argv[1]);

    if (cpu.errno != CPU_OK)
    {
        CpuDump(&cpu, stderr);
        CpuDtor (&cpu);
        return -1;
    }

    SetStackPrinterFunc (&cpu.stack, StackPrinterFunc);
    CpuExecute (&cpu);
    CpuDtor (&cpu);

    return 0;
}

