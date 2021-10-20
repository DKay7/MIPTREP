#define DEF_COMMAND(enum_name, n_arg, id, cmd_name, realization, ...)       \
case id:                                                                    \
    realization                                                             \
    break;                                                                  \

switch (cpu->cmd_array[cpu->pc])
{

    #include "../defines_and_setups/commands_defenitions.h"

    default:
        cpu->errno |= CPU_UNKNOWN_CMD_ERR;
        return cpu->errno;
}

#undef DEF_COMMAND
