#define DEF_COMMAND(enum_name, n_arg, cmd_name, realization, ...)           \
case enum_name:                                                             \
    DisAsmWriteOutput (adc, "%-16s\t", cmd_name);                           \
                                                                            \
    for (int i = 0; i < n_arg; ++i)                                         \
    {                                                                       \
        DisAsmParseArg(adc);                                                \
    }                                                                       \
    DisAsmWriteOutput (adc, "\n");                                          \
    break;                                                                  

switch (adc->cmd_array[adc->ip] & ~(IMMEDIATE_CONST | REGISTER_VALUE | RAM_VALUE))
{
    #include "../defines_and_setups/commands_defenitions.h"

    default:
        adc->errno |= DISASM_UNKNOWN_CMD_ERR;
        return adc->errno;
}

#undef DEF_COMMAND
