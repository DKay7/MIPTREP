#include "assembler/asm.h"
#include "machine/cpu.h"
#include "disassembler/disasm.h"

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int main ()
{   
    AsmUnitTest ();
    CpuUnitTest ();
    DisAsmUnitTest (); 
    
    return 0;
}