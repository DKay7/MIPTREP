#define DEF_ERR_CODE(enum_name, id, text)  \
    if (err_code & id)                     \
    {                                      \
        fprintf (logfile, text);          \
        err_code -= id;                    \
    }                                      \


#include "../defines_and_setups/asm_errors_defenitions.h"

#undef DEF_ERR_CODE