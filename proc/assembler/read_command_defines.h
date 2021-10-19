#define DEF_COMMAND(enum_name, n_args, id, str_cmd_name, ...)                           \
    if (strcmp (cmd_name, str_cmd_name) == 0)                                           \
    {                                                                                   \
        fprintf (listing_file, "%-32s\t|\t%04X\t|\t%04X\t|\t", command, acc->ip, id);   \
        acc->cmd_array[acc->ip] = id;                                                   \
        acc->ip += sizeof (unsigned char);                                              \
                                                                                        \
        if (GetArg (acc, command + shift, n_args, listing_file) != ASMCC_OK)            \
        {                                                                               \
            acc->asm_errno |= ASMCC_ERR_READING_CMD_ARGS;                               \
            return acc->asm_errno;                                                      \
        }                                                                               \
        fprintf (listing_file, "\n");                                                   \
    } else                                                                              \

#include "../defines_and_setups/commands_defenitions.h"

/*else*/
{
    acc->asm_errno |= ASMCC_INVALID_COMMAND;
    return acc->asm_errno;
}
