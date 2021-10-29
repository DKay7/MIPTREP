#ifndef DEF_ERR_CODE
#define DEF_ERR_CODE(...)
#endif

DEF_ERR_CODE (CPU_OK, 0x000, "No errors founded\n")
DEF_ERR_CODE (CPU_NOT_ENOUGH_VALUES_IN_STACK, 0x001, "Not enough values in stack\n")
DEF_ERR_CODE (CPU_ZERO_DIVISION_ERR, 0x002, "Zero division error\n")
DEF_ERR_CODE (CPU_INTERNAL_STACK_ERR, 0x004, "Internal stack error\n")
DEF_ERR_CODE (CPU_UNKNOWN_CMD_ERR, 0x008, "Unknown command\n")
DEF_ERR_CODE (CPU_ERROR_READING_BIN_FILE, 0x010, "Error reading binary file\n")
DEF_ERR_CODE (CPU_CODE_END_REACHED, 0x020, "End of the code was reached\n")
DEF_ERR_CODE (CPU_REGS_OVERFLOW, 0x040, "Accessing register which doesn't exist!\n")
DEF_ERR_CODE (CPU_RAM_OVERFLOW, 0x080, "CPU RAM overflow!\n")
DEF_ERR_CODE (CPU_ARG_READING_ERR, 0x100, "CPU error while reading command arguments!\n")


