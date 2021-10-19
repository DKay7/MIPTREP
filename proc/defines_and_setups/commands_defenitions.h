#ifndef DEF_COMMAND
#define DEF_COMMAND(...)
#endif

#ifndef CHECK_STACK
#define CHECK_STACK(stack_code) {               \
    if (stack_code != STACK_OK)                 \
    {                                           \
        proc_errno |= PROC_INTERNAL_STACK_ERR;  \
        return proc_errno;                      \
    }}
#endif

#ifndef CHECK_STACK_SIZE
#define CHECK_STACK_SIZE(stack_size, required_stack_size)               \
    if (stack_size < required_stack_size)                               \
    {                                                                   \
        proc_errno = proc_errno | PROC_NOT_ENOUGH_VALUES_IN_STACK;      \
        return proc_errno;                                              \
    }
#endif

#ifndef CHECK_ZERO_VALUE
#define CHECK_ZERO_VALUE(value)                             \
    if (fabs (second_term) < EPSILON)                       \
    {                                                       \
        proc_errno = proc_errno | PROC_ZERO_DIVISION_ERR;   \
        return proc_errno;                                  \
    }
#endif

// name, n_args, id, str_name, cmd_realization
DEF_COMMAND (HLT, 0, 0, "hlt",
	{
	    return proc_errno;
    })
//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
  DEF_COMMAND (PUSH, 1, 1, "push",
	       {
	       for (int i = 0; i < n_arg; i++)
	       {
	       stack_type value = ProcGetArgument (cmd_array, *pc);
	       int stack_code = StackPush (stack, value);
	       CHECK_STACK (stack_code)}
	       return proc_errno;}

)

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  DEF_COMMAND (POP, 0, 2, "pop",
	       {
	       CHECK_STACK_SIZE (stack->size, 1)
	       stack_type value = STACK_DATA_POISON;
	       int stack_code = StackPop (stack, &value);
	       /*TODO add registers */
	       CHECK_STACK (stack_code) return proc_errno;}

)
//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
  DEF_COMMAND (ADD, 0, 3, "add",
	       {
	       CHECK_STACK_SIZE (stack->size, 2)
	       stack_type fisrt_term = STACK_DATA_POISON;
	       stack_type second_term = STACK_DATA_POISON;
	       int stack_code1 = StackPop (stack, &fisrt_term);
	       int stack_code2 = StackPop (stack, &second_term);
	       CHECK_STACK (stack_code1)
	       CHECK_STACK (stack_code2)
	       StackPush (stack, fisrt_term + second_term);
	       return proc_errno;}
)
//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

DEF_COMMAND (SUB, 0, 4, "sub", {
	       CHECK_STACK_SIZE (stack->size, 2)
	       stack_type fisrt_term = STACK_DATA_POISON;
	       stack_type second_term = STACK_DATA_POISON;
	       int stack_code1 = StackPop (stack, &fisrt_term);
	       int stack_code2 = StackPop (stack, &second_term);
	       CHECK_STACK (stack_code1)
	       CHECK_STACK (stack_code2)
	       StackPush (stack, fisrt_term - second_term);
	       return proc_errno;
})

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

DEF_COMMAND (DIV, 0, 5, "div", {
	       CHECK_STACK_SIZE (stack->size, 2)
	       stack_type fisrt_term = STACK_DATA_POISON;
	       stack_type second_term = STACK_DATA_POISON;
	       int stack_code1 = StackPop (stack, &fisrt_term);
	       int stack_code2 = StackPop (stack, &second_term);
	       CHECK_STACK (stack_code1)
	       CHECK_STACK (stack_code2)
	       CHECK_ZERO_VALUE (second_term)
	       StackPush (stack, fisrt_term / second_term);
	       return proc_errno;
})

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
  DEF_COMMAND (MUL, 0, 6, "mul", {
	       CHECK_STACK_SIZE (stack->size, 2)
	       stack_type fisrt_term = STACK_DATA_POISON;
	       stack_type second_term = STACK_DATA_POISON;
	       int stack_code1 = StackPop (stack, &fisrt_term);
	       int stack_code2 = StackPop (stack, &second_term);
	       CHECK_STACK (stack_code1)
	       CHECK_STACK (stack_code2)
	       StackPush (stack, fisrt_term * second_term);
	       return proc_errno;
})
//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
  DEF_COMMAND (OUT, 0, 7, "out",
	       {
	       CHECK_STACK_SIZE (stack->size, 1)
	       stack_type element = STACK_DATA_POISON;
	       int stack_code = StackPop (stack, &element);
	       CHECK_STACK (stack_code)
	       printf ("%lg\n", element); return proc_errno;}
)
//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
  DEF_COMMAND (IN, 0, 8, "in",
	       {
	       stack_type element = STACK_DATA_POISON;
	       scanf ("%lg ", &element);
	       int stack_code = StackPush (stack, element);
	       CHECK_STACK (stack_code) return proc_errno;}
)
//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
  DEF_COMMAND (DUMP, 0, 9, "dump",
	       {
	       printf ("ERROR NUM: %d\n", proc_errno);
	       StackDump (stack); return proc_errno;}
)
//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
  DEF_COMMAND (VALIDATE, 0, 10, "validate", 
  {
	       StackValidate (stack, STACK_EXTERNAL_FUNC_CODE);
	       return proc_errno;
})
