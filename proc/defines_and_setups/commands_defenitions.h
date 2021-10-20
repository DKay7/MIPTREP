#ifndef DEF_COMMAND
#define DEF_COMMAND(...)
#endif


//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

// name, n_args, id, str_name, cmd_realization
DEF_COMMAND (HLT, 0, 0, "hlt",
	{
		cpu->errno |= CPU_CODE_END_REACHED;
	}
)

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

DEF_COMMAND (PUSH, 1, 1, "push",
	{	
		arg_t value = STACK_DATA_POISON;
		CpuGetArgument (cpu, &value);
		int stack_code = StackPush (&cpu->stack, value);
		CHECK_STACK (cpu, stack_code)
	}
)

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

DEF_COMMAND (POP, 0, 2, "pop",
	{
		CHECK_STACK_SIZE (cpu, cpu->stack.size, 1)
		arg_t value = STACK_DATA_POISON;
		int stack_code = StackPop (&cpu->stack, &value);
		/*TODO add registers */
		CHECK_STACK (cpu, stack_code)
	}
)

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

DEF_COMMAND (ADD, 0, 3, "add",
	{
		CHECK_STACK_SIZE (cpu, cpu->stack.size, 2)
		arg_t fisrt_term = STACK_DATA_POISON;
		arg_t second_term = STACK_DATA_POISON;
		int stack_code1 = StackPop (&cpu->stack, &fisrt_term);
		int stack_code2 = StackPop (&cpu->stack, &second_term);
		CHECK_STACK (cpu, stack_code1)
		CHECK_STACK (cpu, stack_code2)
		StackPush (&cpu->stack, fisrt_term + second_term);
	}
)

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

DEF_COMMAND (SUB, 0, 4, "sub", 
	{
		CHECK_STACK_SIZE (cpu, cpu->stack.size, 2)
		arg_t fisrt_term = STACK_DATA_POISON;
		arg_t second_term = STACK_DATA_POISON;
		int stack_code1 = StackPop (&cpu->stack, &fisrt_term);
		int stack_code2 = StackPop (&cpu->stack, &second_term);
		CHECK_STACK (cpu, stack_code1)
		CHECK_STACK (cpu, stack_code2)
		StackPush (&cpu->stack, fisrt_term - second_term);
	}
)	

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

DEF_COMMAND (DIV, 0, 5, "div", 
	{
		CHECK_STACK_SIZE (cpu, cpu->stack.size, 2)
		arg_t fisrt_term = STACK_DATA_POISON;
		arg_t second_term = STACK_DATA_POISON;
		int stack_code1 = StackPop (&cpu->stack, &fisrt_term);
		int stack_code2 = StackPop (&cpu->stack, &second_term);
		CHECK_STACK (cpu, stack_code1)
		CHECK_STACK (cpu, stack_code2)
		CHECK_ZERO_VALUE (cpu, second_term)
		StackPush (&cpu->stack, fisrt_term / second_term);
	}
)

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

DEF_COMMAND (MUL, 0, 6, "mul", 
	{
		CHECK_STACK_SIZE (cpu, cpu->stack.size, 2)
		arg_t fisrt_term = STACK_DATA_POISON;
		arg_t second_term = STACK_DATA_POISON;
		int stack_code1 = StackPop (&cpu->stack, &fisrt_term);
		int stack_code2 = StackPop (&cpu->stack, &second_term);
		CHECK_STACK (cpu, stack_code1)
		CHECK_STACK (cpu, stack_code2)
		StackPush (&cpu->stack, fisrt_term * second_term);
	}
)

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

DEF_COMMAND (OUT, 0, 7, "out",
	{
		CHECK_STACK_SIZE (cpu, cpu->stack.size, 1)
		arg_t element = STACK_DATA_POISON;
		int stack_code = StackPop (&cpu->stack, &element);
		CHECK_STACK (cpu, stack_code)
		printf ("%lg\n", element);
	}
)

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

DEF_COMMAND (IN, 0, 8, "in",
	{
		arg_t element = STACK_DATA_POISON;
		scanf ("%lg", &element);
		int stack_code = StackPush (&cpu->stack, element);
		CHECK_STACK (cpu, stack_code)
	}
)

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

DEF_COMMAND (DUMP, 0, 9, "dump",
	{
	    CpuDump (cpu, stdout); 
	}
)

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

DEF_COMMAND (STACK_DUMP, 0, 10, "dumpstk",
	{
	    StackDump (&cpu->stack, stdout); 
	}
)

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

DEF_COMMAND (VALIDATE, 0, 11, "validate", 
  	{
	    StackValidate (&cpu->stack, STACK_EXTERNAL_FUNC_CODE);
	}
)
