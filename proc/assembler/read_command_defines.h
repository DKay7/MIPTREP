#define DEF_COMMAND(enum_name, n_args, str_cmd_name, realization, arg_const ...)                                \
    if (strcmp (cmd_name, str_cmd_name) == 0)                                                                   \
    {                                                                                                           \
        fprintf (listing_file, "%-32s\t|\t%02lX\t|\t", command, acc->ip);                                       \
        acc->cmd_array[acc->ip] = enum_name;                                                                    \
        acc->ip += sizeof (unsigned char);                                                                      \
                                                                                                                \
        if (n_args == 0)                                                                                        \
        {                                                                                                       \
            fprintf (listing_file, "%02d\t|\t", enum_name);                                                     \
        }                                                                                                       \
                                                                                                                \
        else if (GetArg (acc, command + shift, arg_const, listing_file) != ASMCC_OK)                            \
        {                                                                                                       \
            acc->asm_errno |= ASMCC_ERR_READING_CMD_ARGS;                                                       \
        }                                                                                                       \
        fprintf (listing_file, "\n");                                                                           \
    } else                                                                                                      \

#include "../defines_and_setups/commands_defenitions.h"

/*else*/
{   
    int result = CheckAndProcessLabel (acc, command, listing_file);
    
    if (!result)
    {
        acc->asm_errno |= ASMCC_INVALID_COMMAND;
        free (cmd_name);
        return acc->asm_errno;
    }
}

#undef DEF_COMMAND