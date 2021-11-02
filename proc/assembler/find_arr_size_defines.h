#define DEF_COMMAND(enum_name, n_args, str_cmd_name, ...)                               \
    if (strcmp (cmd_name, str_cmd_name) == 0)                                           \
    {                                                                                   \
        num_bytes += sizeof (unsigned char) + n_args * sizeof (arg_t);                  \
    } else                                                                              

#include "../defines_and_setups/commands_defenitions.h"

/*else*/
{   
    free (cmd_name);
    continue;
}

#undef DEF_COMMAND