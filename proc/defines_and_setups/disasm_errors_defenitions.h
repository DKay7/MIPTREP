#ifndef DEF_ERR_CODE
#define DEF_ERR_CODE(...)
#endif

DEF_ERR_CODE (DISASM_OK,                    0x000, "No errors founded\n")
DEF_ERR_CODE (DISASM_ERR_READING_CMD_NAME,  0x002, "Error reading command name\n")
DEF_ERR_CODE (DISASM_ERR_READING_CMD_ARGS,  0x004, "Error reading command arguments\n")
DEF_ERR_CODE (DISASM_UNKNOWN_CMD_ERR,       0x008, "Unknown command id\n")
DEF_ERR_CODE (DISASM_FILE_OPENING_ERR,      0x010, "Error while opening file\n")
DEF_ERR_CODE (DISASM_ERR_ALLOCATING_MEMORY, 0x020, "Error while allocating memory\n")
DEF_ERR_CODE (DISASM_ERR_READING_BIN_FILE,  0x040, "Error while reading binary file\n")
