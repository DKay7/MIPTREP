#ifndef DEF_ERR_CODE
#define DEF_ERR_CODE(...)
#endif

DEF_ERR_CODE (ASMCC_OK, 0x000, "No errors founded\n")
DEF_ERR_CODE (ASMCC_INVALID_COMMAND, 0x001, "Invalid command\n")
DEF_ERR_CODE (ASMCC_ERR_READING_CMD_NAME, 0x002, "Error reading command name\n")
DEF_ERR_CODE (ASMCC_ERR_READING_CMD_ARGS, 0x004, "Error reading command arguments\n")
DEF_ERR_CODE (ASMCC_WRONG_NUM_OF_CMD_ARGS, 0x008, "Wrong number of command arguments\n")
DEF_ERR_CODE (ASMCC_FILE_OPENING_ERR, 0x010, "Error while opening file\n")
DEF_ERR_CODE (ASMCC_ERR_ALLOCATING_MEMORY, 0x020, "Error while allocating memory\n")
DEF_ERR_CODE (ASMCC_UNKNOWN_REG_NAME_ERR, 0x040, "Unknown register name\n")
DEF_ERR_CODE (ASMCC_LABEL_NOT_RESOLWED, 0x080, "Label wasn't resolved!\n")


