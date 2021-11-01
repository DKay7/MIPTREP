#ifndef CPU_H
#define CPU_H


//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

#include "../libs/stack/stack.h"
#include "../defines_and_setups/errors.h"
#include "../defines_and_setups/cpu_setup.h"
#include "../defines_and_setups/asm_setup.h"

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

#define CpuDump(cpu, logfile) CpuDumpFunction (cpu, logfile, __LINE__, #cpu, __PRETTY_FUNCTION__, __FILE__)

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

typedef struct
{
    size_t size_x = 0;
    size_t size_y = 0;
    size_t start_ptr = 0;
} VR;

typedef struct
{
  Stack stack;    
  unsigned char* cmd_array;      
  size_t cmd_array_size;         
  arg_t* regs;
  arg_t* ram;
  VR vr = {};
  long unsigned pc;
  int errno = CPU_OK;
} Cpu;

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int CpuExecute(Cpu* cpu);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int CpuProcessComand (Cpu* cpu);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int CpuCtor (Cpu* cpu);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int CpuDtor (Cpu* cpu);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int CpuOpenFile (Cpu* cpu, const char* filename);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

arg_t* CpuGetArgument (Cpu* cpu);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void CpuDumpFunction (Cpu* cpu, FILE* logfile, int line, const char* cpu_name, const char* func_name, const char* file_name);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int CpuUnitTest();

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
#endif