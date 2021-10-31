#include "cpu.h"
#include "../defines_and_setups/errors.h"
#include "../libs/bin_text_lib/binlib.h"
#include "../defines_and_setups/asm_setup.h"
#include <assert.h>
#include <math.h>
#include <string.h>

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int CpuExecute(Cpu* cpu)
{
    assert (cpu);
    assert (cpu->cmd_array);
    assert (cpu->ram);

    while (1)
    {   
        CpuProcessComand (cpu);

        if (cpu->errno != CPU_OK)
        {
            break;
        }
    }

    return cpu->errno;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int CpuProcessComand (Cpu* cpu)
{   
    assert (cpu);
    assert (cpu->cmd_array);
    assert (cpu->ram);

    #include "process_cmd_defines.h"

    return cpu->errno;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int CpuCtor (Cpu* cpu)
{
    Stack stack = {};
    StackCtor (&stack, STACK_INIT_SIZE);
    cpu->stack = stack;

    cpu->ram = (arg_t*) calloc (RAM_SIZE, sizeof (arg_t));
    cpu->regs = (arg_t*) calloc (REG_SIZE, sizeof (arg_t));

    cpu->pc = 0;
    cpu->cmd_array_size = 0;
    cpu->errno = CPU_OK;

    return cpu->errno;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int CpuDtor (Cpu* cpu)
{   
    assert (cpu);
    StackDtor (&cpu->stack);

    if (cpu->cmd_array)
    {
        free (cpu->cmd_array);
    }

    free (cpu->ram);
    free (cpu->regs);

    return CPU_OK;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int CpuOpenFile (Cpu* cpu, const char* filename)
{   
    assert (cpu);
    assert (filename);

    if (cpu->cmd_array)
    {
        free (cpu->cmd_array);
    }

    BinHeader correct_bh = {};
    BinHeaderCtor (&correct_bh, SIGNATURE, CC_VERSION);
    int code = ReadFromBinary (&correct_bh, &cpu->cmd_array, &cpu->cmd_array_size, filename);

    if (code != 0)
    {   
        cpu->errno |= CPU_ERROR_READING_BIN_FILE;
        return CPU_ERROR_READING_BIN_FILE;
    }

    return cpu->errno;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

arg_t* CpuGetArgument (Cpu* cpu)
{   
    assert (cpu);


    arg_t* ret_value = NULL;

    int current_cmd = cpu->cmd_array[cpu->pc];
    long unsigned arg_index =  cpu->pc + sizeof (unsigned char);

    if (current_cmd & IMMEDIATE_CONST)
    {   
        ret_value = (arg_t*)(cpu->cmd_array + arg_index);
        cpu->pc += sizeof (arg_t);
    }

    if (current_cmd & REGISTER_VALUE)
    {
        arg_t reg_index = *(arg_t*)(cpu->cmd_array + arg_index);
        ret_value = &cpu->regs[(int) reg_index];

        cpu->pc += sizeof (arg_t);
    }

    if (current_cmd & RAM_VALUE)
    {   
        assert (current_cmd & IMMEDIATE_CONST || current_cmd & REGISTER_VALUE);
 
        ret_value = (arg_t*) &cpu->cmd_array[(int) *ret_value];
        cpu->pc += sizeof (arg_t);
    }

    return ret_value;

}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void CpuDumpFunction (Cpu* cpu, FILE* logfile, int line, const char* cpu_name, const char* func_name, const char* file_name)
{   
    assert (cpu);
    assert (logfile);

    int err_code = cpu->errno;

    if (err_code == STACK_OK)
    {
        fprintf (logfile, GREEN_COLOR("\nCPU [OK]: "));
    }
    
    else
    {
        fprintf (logfile, RED_COLOR("\nCPU [ERROR][ERR_CODE: 0x%X]"), err_code);
    }

    fprintf (logfile,"Dump for \"%s\" called in func. %s, line %d, file %s'\n", cpu_name, func_name, line, file_name);
 

    if (err_code != CPU_OK)
    {
        fprintf (logfile, "One or more errors were reached while executing code\n"
                          "Here they are:\n");
    }

    #include "cpu_dump_errors_defines.h"

    if (err_code != 0)
    {
        fprintf (logfile, "Unknown error with code %X", err_code);
    }

    fprintf (logfile, "{\n"
                      "\t-->Mem[%p]\n\t{\n", cpu->ram);
    
    for (int i = 0; i < RAM_SIZE; ++i)
    {   
        if (cpu->ram[i] != 0)
            fprintf (logfile, "\t\t[%d]:\t{%lg}\n", i, cpu->ram[i]);
    }

    fprintf (logfile, "\t}\n\n"
                      "\t-->Regs[%p]\n\t{\n", cpu->regs);

    for (int i = 0; i < REG_SIZE; ++i)
    {
        fprintf (logfile, "\t\t[%d]:\t{%lg}\n", i, cpu->regs[i]);
    }               

    fprintf (logfile, "\t}\n\n"
                      "\t-->Stack[]\n\t{\n");

    for (size_t i = 0; i < cpu->stack.size; ++i)
    {
        fprintf (logfile, "\t\t[%ld]:\t{%lg}\n", i, cpu->stack.data[i]);
    }             
    fprintf (logfile, "\t}\n}\n");

    return;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx


void PrinterFunc (stack_type* el)
{
    printf ("%lf", *el);
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int CpuUnitTest()
{   
    Cpu cpu = {};
    CpuCtor (&cpu);
    CpuOpenFile (&cpu, "asm_result.mc");
    //printf ("%d", cpu.cmd_array[1]);
    SetStackPrinterFunc (&cpu.stack, PrinterFunc);
    CpuExecute (&cpu);
    CpuDtor (&cpu);

    return 0;
}

