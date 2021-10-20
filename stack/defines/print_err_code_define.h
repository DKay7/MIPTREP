#define DEF_ERR_CODE(enum_name, id, text)  \
    if (err_code & id)                     \
    {                                      \
        printf (RED_COLOR(text));          \
        err_code -= id;                    \
    }                                      \


#include "err_code_defines.h"

#undef DEF_ERR_CODE