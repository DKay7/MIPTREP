#ifndef DEF_ERR_CODE
#define DEF_ERR_CODE(...)
#endif

DEF_ERR_CODE (STACK_OK, 0x000, "No errors founded\n")
DEF_ERR_CODE (STACK_MEM_ALLOCK_ERR, 0x001, "Memory allocation error\n")
DEF_ERR_CODE (STACK_INCREASE_ERR, 0x002, "Error while increasing stack\n")
DEF_ERR_CODE (STACK_DECREASE_ERR, 0x004, "Error while decreasing stack\n")
DEF_ERR_CODE (STACK_CTOR_DBL_CALL, 0x008, "Stack constructor was called twice\n")
DEF_ERR_CODE (STACK_DTOR_DBL_CALL, 0x010, "Stack destructor was called twice\n")
DEF_ERR_CODE (STACK_INCORRECT_DATA_PTR, 0x020, "Incorrect pointer to start of buffer founded\n")
DEF_ERR_CODE (STACK_WRONG_START_HUMMINGBIRD, 0x040, "Changes in start hummingbird founded\n")
DEF_ERR_CODE (STACK_WRONG_END_HUMMINGBIRD, 0x080, "Changes in end hummingbird founded\n")
DEF_ERR_CODE (STACK_INCORRECT_SIZE, 0x100, "Stack size is incorrect\n")
DEF_ERR_CODE (STACK_INCORRECT_CAPACITY, 0x200, "Stack capcity is incorrect\n")
DEF_ERR_CODE (STACK_WRONG_HASH_SUM, 0x400, "Mismacth of hash sum founded\n")
DEF_ERR_CODE (STACK_NOT_CREATED, 0x800, "Stack was descructed and wasn't created\n")



