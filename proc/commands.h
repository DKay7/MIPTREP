#ifndef DEF_COMMAND
#define DEF_COMMAND(...)
#endif

// name, n_args, id, str_name, cmd_len
DEF_COMMAND (HLT,       0,      0,  "hlt")
DEF_COMMAND (PUSH,      1,      1,  "push")
DEF_COMMAND (POP,       0,      2,  "pop")
DEF_COMMAND (ADD,       0,      3,  "add")
DEF_COMMAND (SUB,       0,      4,  "sub")
DEF_COMMAND (DIV,       0,      5,  "div")
DEF_COMMAND (MUL,       0,      6,  "mul")
DEF_COMMAND (OUT,       0,      8,  "out")
DEF_COMMAND (IN,        0,      9,  "in")
DEF_COMMAND (DUMP,      0,      10, "dump")
DEF_COMMAND (VALIDATE,  0,      11, "validate")