#include "disasm.h"
#include "../defines_and_setups/errors.h"
#include "../libs/bin_text_lib/binlib.h"
#include "../defines_and_setups/asm_setup.h"
#include "../defines_and_setups/cpu_setup.h"
#include "../libs/text_lib/texlib.h"
#include <assert.h>
#include <malloc.h>
#include <stdarg.h>

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int DisAsmCtor (AsmDecompiler* adc)
{
    assert (adc);

    adc->buffer = NULL;
    adc->buf_ptr = adc->buffer;
    adc->cmd_array = NULL;
    adc->ip = 0;
    adc->buf_size = 0;
    adc->errno = DISASM_OK;

    return adc->errno;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void DisAsmDtor (AsmDecompiler* adc)
{
    assert (adc);

    if (adc->buffer)
    {
        free (adc->buffer);
    }

    if (adc->cmd_array)
    {
        free (adc->cmd_array);
    }
    adc->cmd_array = NULL;
    adc->buffer = NULL;
    adc->buf_ptr = NULL;
    adc->buf_size = 0;
    adc->cmd_array_size = 0;
    adc->ip = 0;
    adc->errno = 0;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int DisAsmOpenFile (AsmDecompiler* adc, const char* filename)
{
    assert (adc);
    assert (filename);

    if (adc->cmd_array)
    {
        free (adc->cmd_array);
    }

    BinHeader correct_bh = {};
    BinHeaderCtor (&correct_bh, SIGNATURE, CC_VERSION);
    int ret_code = ReadFromBinary (&correct_bh, &adc->cmd_array, &adc->cmd_array_size, filename);

    if (ret_code != 0)
    {   
        adc->errno |= DISASM_INCOMPATIBLE_BIN_HEADER;
        adc->errno |= DISASM_ERR_READING_BIN_FILE;
        return adc->errno;
    }

    adc->buffer  = (char*) calloc (adc->cmd_array_size, MAX_CMD_LEN * (sizeof (char) + sizeof (arg_t)));

    if (!adc->buffer)
    {
        adc->errno |= DISASM_ERR_ALLOCATING_MEMORY;
        return adc->errno;
    }

    adc->buf_ptr = adc->buffer;
    adc->buf_size = MAX_CMD_LEN * (sizeof (char) + sizeof (arg_t));

    return adc->errno;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int DisAsmParseArg (AsmDecompiler* adc)
{
    int command_id = adc->cmd_array[adc->ip];
    int is_ram = 0;

    if (command_id & RAM_VALUE)
    {   
        is_ram = 1;
        DisAsmWriteOutput(adc, "[ ");
    }

    if (command_id & REGISTER_VALUE)
    {   
        #include "disasm_regs_defines.h"
        adc->ip += sizeof (arg_t);

    }

    else if (command_id & IMMEDIATE_CONST)
    {   
        arg_t arg = *(arg_t*) (adc->cmd_array + adc->ip + sizeof (unsigned char));

        DisAsmWriteOutput(adc, "%lg", arg);
        adc->ip += sizeof (arg_t);
    }

    if (is_ram)
    {
        DisAsmWriteOutput(adc, " ]");
    }

    return adc->errno;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int DisAcmProcessFile (AsmDecompiler* adc, const char* filename)
{   

    while (adc->ip < adc->cmd_array_size)
    {   
        #include "disasm_cmd_defines.h"
        adc->ip += sizeof (unsigned char);
    }

    SaveToFile (adc->buffer, filename);

    return adc->errno;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int DisAsmWriteOutput (AsmDecompiler* adc, const char* format,  ...)
{
    va_list args;
    va_start (args, format);
    int num_written = vsnprintf (adc->buf_ptr, adc->buf_size, format, args);
    adc->buf_ptr += num_written; 
    va_end (args);

    return adc->errno;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void DisAsmDump (AsmDecompiler* adc, FILE* logfile)
{
    assert (adc);
    assert (logfile);

    int err_code = adc->errno;

    if (err_code == DISASM_OK)
    {
        fprintf (logfile, "\nDisassembler is OK!\n");
    }

    if (err_code != DISASM_OK)
    {
        fprintf (logfile, "\nOne or more errors were reached while decompiling code.\n"
                    "Here they are:\n\n");
    }

    #include "dump_errors_defines.h"

    if (err_code != 0)
    {
        fprintf (logfile, "Unknown error with code %X", err_code);
    }

    return;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
