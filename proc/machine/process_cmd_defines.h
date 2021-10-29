#define DEF_COMMAND(enum_name, n_arg, cmd_name, realization, ...)           \
case enum_name:                                                             \
    realization                                                             \
    break;                                                                  \

switch (cpu->cmd_array[cpu->pc] & ~(IMMEDIATE_CONST | REGISTER_VALUE | RAM_VALUE))
{
    #include "../defines_and_setups/commands_defenitions.h"

    default:
        cpu->errno |= CPU_UNKNOWN_CMD_ERR;
        return cpu->errno;
}

#undef DEF_COMMAND
