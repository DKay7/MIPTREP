#ifndef DEF_COMMAND
#define DEF_COMMAND(...)
#endif

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

// Optional and required arguments.
// Figured out by high bit (1 -- required, 0 -- optional)
#define ARG(number, type) (((0x1 << 4) | (type)) << (number * 4))
#define OPT_ARG(number, type) (((0x0 << 4) | (type)) << (number * 4))
#define NO_ARGS (0x0 << 4)

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

// name, n_args, id, str_name, cmd_realization
DEF_COMMAND (HLT, 0, 0, "hlt",
	{
		cpu->errno |= CPU_CODE_END_REACHED;
	}, 
	NO_ARGS
)

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

DEF_COMMAND (PUSH, 1, 1, "push",
	{	
		arg_t value = STACK_DATA_POISON;
		CpuGetArgument (cpu, &value);
		int stack_code = StackPush (&cpu->stack, value);
		CHECK_STACK (cpu, stack_code)
	}, 
	ARG (0, (RAM_VALUE_LOW | REGISTER_VALUE_LOW | IMMEDIATE_CONST_LOW))
)

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

DEF_COMMAND (POP, 1, 2, "pop",
	{
		CHECK_STACK_SIZE (cpu, cpu->stack.size, 1)
		int cmd_id = cpu->cmd_array[cpu->pc];
		if (cmd_id & RAM_VALUE)
		{	
			cpu->pc += sizeof (unsigned char);

			// if ram_id is immedeate const
			int ram_id = cpu->cmd_array[cpu->pc];

			// if ram_id is register
			if (cmd_id & REGISTER_VALUE)
			{
				ram_id = cpu->regs[ram_id];
			}
			int stack_code = StackPop (&cpu->stack, &cpu->ram[ram_id]);
			CHECK_STACK (cpu, stack_code)
		}

		else if (cmd_id & REGISTER_VALUE)
		{	
			cpu->pc += sizeof (unsigned char);
			int reg_id = cpu->cmd_array[cpu->pc];
			int stack_code = StackPop (&cpu->stack, &cpu->regs[reg_id]);
			CHECK_STACK (cpu, stack_code)
		}	

		else
		{	
			// no args
			arg_t value = 0;
			int stack_code = StackPop (&cpu->stack, &value);
			CHECK_STACK (cpu, stack_code)
		}
	
	},
	OPT_ARG (0, (RAM_VALUE_LOW | REGISTER_VALUE_LOW))
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
	},
	NO_ARGS
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
	},
	NO_ARGS
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
	},
	NO_ARGS
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
	},
	NO_ARGS
)

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

DEF_COMMAND (OUT, 0, 7, "out",
	{
		CHECK_STACK_SIZE (cpu, cpu->stack.size, 1)
		arg_t element = STACK_DATA_POISON;
		int stack_code = StackPop (&cpu->stack, &element);
		CHECK_STACK (cpu, stack_code)
		printf ("%lg\n", element);
	},
	NO_ARGS
)

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

DEF_COMMAND (IN, 0, 8, "in",
	{
		arg_t element = STACK_DATA_POISON;
		scanf ("%lg", &element);
		int stack_code = StackPush (&cpu->stack, element);
		CHECK_STACK (cpu, stack_code)
	},
	NO_ARGS
)

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

DEF_COMMAND (DUMP, 0, 9, "dump",
	{
	    CpuDump (cpu, stdout); 
	},
	NO_ARGS
)

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

DEF_COMMAND (DUMP_STK, 0, 10, "dumpstk",
	{
	    StackDump (&cpu->stack, stdout); 
	},
	NO_ARGS
)

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

DEF_COMMAND (VALIDATE, 0, 11, "validate", 
  	{
	    StackValidate (&cpu->stack, STACK_EXTERNAL_FUNC_CODE);
	},
	NO_ARGS
)
