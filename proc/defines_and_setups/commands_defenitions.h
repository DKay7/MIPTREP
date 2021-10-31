#ifndef DEF_COMMAND
#define DEF_COMMAND(...)
#endif

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

// Optional and required arguments.
// Figured out by high bit (1 -- required, 0 -- optional)
#define ARG(    number, type)  ((0x1 | (type)) >> (number * 4))
#define OPT_ARG(number, type)  ((0x0 | (type)) >> (number * 4))
#define NO_ARGS                (0x0)
#define ARG_MASK                0xFF

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

#define PUSH(arg)	StackPush (&cpu->stack, (arg))
#define POP(adr)	StackPop (&cpu->stack, (adr))

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

// name, n_args, str_name, cmd_realization
DEF_COMMAND (HLT, 0, "hlt",
	{
		cpu->errno |= CPU_CODE_END_REACHED;
		break;
	}, 
	NO_ARGS
)

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

DEF_COMMAND (PUSH, 1, "push",
	{	
		arg_t* value =  CpuGetArgument (cpu);
		int stack_code = PUSH (*value);
		CHECK_STACK (cpu, stack_code)
	    cpu->pc += sizeof (unsigned char);
	}, 
	ARG (0, (RAM_VALUE | REGISTER_VALUE | IMMEDIATE_CONST))
)

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

DEF_COMMAND (POP, 1, "pop",
	{	
		CHECK_STACK_SIZE (cpu, cpu->stack.size, 1)
		arg_t* value =  CpuGetArgument (cpu);

		int stack_code = 0;

		if (!value)
		{	
			// no args
			arg_t val = 0;
			stack_code = POP (&val);
		}
		
		else
		{
			stack_code = POP (value);
		}

		CHECK_STACK (cpu, stack_code)
	    cpu->pc += sizeof (unsigned char);
	},
	OPT_ARG (0, (RAM_VALUE | REGISTER_VALUE))
)

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

DEF_COMMAND (JMP, 1, "jmp",
	{
		arg_t* new_pc = CpuGetArgument (cpu);
		cpu->pc = (unsigned long) (*new_pc);
		printf ("NEW PC: %lg\n", *new_pc);
	},
	ARG (0, (IMMEDIATE_CONST))
)

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

DEF_COMMAND (JE, 1, "je",
	{	
		CHECK_STACK_SIZE (cpu, cpu->stack.size, 2)
		arg_t first_term = STACK_DATA_POISON;
		arg_t second_term = STACK_DATA_POISON;
		int stack_code1 = StackPop (&cpu->stack, &first_term);
		int stack_code2 = StackPop (&cpu->stack, &second_term);
		CHECK_STACK (cpu, stack_code1)
		CHECK_STACK (cpu, stack_code2)

		if (fabs (first_term - second_term) < EPSILON)
		{			
			arg_t* new_pc = CpuGetArgument (cpu);
			cpu->pc = ((unsigned long) (*new_pc));
		}
		else
		{
	  	  cpu->pc += sizeof (unsigned char);
		}


	},
	ARG (0, (IMMEDIATE_CONST))
)

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

DEF_COMMAND (JA, 1, "ja",
	{	
		CHECK_STACK_SIZE (cpu, cpu->stack.size, 2)
		arg_t first_term = STACK_DATA_POISON;
		arg_t second_term = STACK_DATA_POISON;
		int stack_code1 = POP (&first_term);
		int stack_code2 = POP (&second_term);
		CHECK_STACK (cpu, stack_code1)
		CHECK_STACK (cpu, stack_code2)

		if (second_term > first_term)
		{			
			arg_t* new_pc = CpuGetArgument (cpu);
			cpu->pc = ((unsigned long) (*new_pc));
		}
		else
		{
	  	  cpu->pc += sizeof (unsigned char);
		}

	},
	ARG (0, (IMMEDIATE_CONST))
)

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

DEF_COMMAND (JAE, 1, "jae",
	{	
		CHECK_STACK_SIZE (cpu, cpu->stack.size, 2)
		arg_t first_term = STACK_DATA_POISON;
		arg_t second_term = STACK_DATA_POISON;
		int stack_code1 = POP (&first_term);
		int stack_code2 = POP (&second_term);
		CHECK_STACK (cpu, stack_code1)
		CHECK_STACK (cpu, stack_code2)

		if (second_term >= first_term)
		{			
			arg_t* new_pc = CpuGetArgument (cpu);
			cpu->pc = ((unsigned long) (*new_pc));
		}
		else
		{
	  	  cpu->pc += sizeof (unsigned char);
		}

	},
	ARG (0, (IMMEDIATE_CONST))
)

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

DEF_COMMAND (JB, 1, "jb",
	{	
		CHECK_STACK_SIZE (cpu, cpu->stack.size, 2)
		arg_t first_term = STACK_DATA_POISON;
		arg_t second_term = STACK_DATA_POISON;
		int stack_code1 = POP (&first_term);
		int stack_code2 = POP (&second_term);
		CHECK_STACK (cpu, stack_code1)
		CHECK_STACK (cpu, stack_code2)

		if (second_term < first_term)
		{			
			arg_t* new_pc = CpuGetArgument (cpu);
			cpu->pc = ((unsigned long) (*new_pc));
		}
		else
		{
	  	  cpu->pc += sizeof (unsigned char);
		}

	},
	ARG (0, (IMMEDIATE_CONST))
)


//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

DEF_COMMAND (JBE, 1, "jbe",
	{	
		CHECK_STACK_SIZE (cpu, cpu->stack.size, 2)
		arg_t first_term = STACK_DATA_POISON;
		arg_t second_term = STACK_DATA_POISON;
		int stack_code1 = POP (&first_term);
		int stack_code2 = POP (&second_term);
		CHECK_STACK (cpu, stack_code1)
		CHECK_STACK (cpu, stack_code2)

		if (second_term <= first_term)
		{			
			arg_t* new_pc = CpuGetArgument (cpu);
			cpu->pc = ((unsigned long) (*new_pc));
		}
		else
		{
	  	  cpu->pc += sizeof (unsigned char);
		}

	},
	ARG (0, (IMMEDIATE_CONST))
)

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

DEF_COMMAND (CALL, 1, "call",
	{			
		arg_t* new_pc = CpuGetArgument (cpu);
		// CpuGetArgument has already moved pc on arg size so
		// we only has to move pc on command size
		int stack_code = PUSH (cpu->pc + sizeof (unsigned char));
		CHECK_STACK (cpu, stack_code)
		cpu->pc = ((unsigned long) (*new_pc));

	},
	ARG (0, (IMMEDIATE_CONST))
)

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

DEF_COMMAND (RET, 0, "ret",
	{	
		CHECK_STACK_SIZE (cpu, cpu->stack.size, 1)
		arg_t new_pc = -1;
		int stack_code = POP (&new_pc);
		CHECK_STACK (cpu, stack_code)

		cpu->pc = ((unsigned long) (new_pc));
	},
	NO_ARGS
)

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

DEF_COMMAND (ADD, 0, "add",
	{
		CHECK_STACK_SIZE (cpu, cpu->stack.size, 2)
		CHECK_STACK_SIZE (cpu, cpu->stack.size, 2)
		arg_t first_term = STACK_DATA_POISON;
		arg_t second_term = STACK_DATA_POISON;
		int stack_code1 = POP (&first_term);
		int stack_code2 = POP (&second_term);
		CHECK_STACK (cpu, stack_code1)
		CHECK_STACK (cpu, stack_code2)
		PUSH (first_term + second_term);
	    cpu->pc += sizeof (unsigned char);
	},
	NO_ARGS
)

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

DEF_COMMAND (SUB, 0, "sub", 
	{
		CHECK_STACK_SIZE (cpu, cpu->stack.size, 2)
		arg_t fisrt_term = STACK_DATA_POISON;
		arg_t second_term = STACK_DATA_POISON;
		int stack_code1 = POP (&fisrt_term);
		int stack_code2 = POP (&second_term);
		CHECK_STACK (cpu, stack_code1)
		CHECK_STACK (cpu, stack_code2)
		PUSH (second_term - fisrt_term);
	    cpu->pc += sizeof (unsigned char);
	},
	NO_ARGS
)	

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

DEF_COMMAND (DIV, 0, "div", 
	{
		CHECK_STACK_SIZE (cpu, cpu->stack.size, 2)
		arg_t fisrt_term = STACK_DATA_POISON;
		arg_t second_term = STACK_DATA_POISON;
		int stack_code1 = POP (&fisrt_term);
		int stack_code2 = POP (&second_term);
		CHECK_STACK (cpu, stack_code1)
		CHECK_STACK (cpu, stack_code2)
		CHECK_ZERO_DIVISION (cpu, second_term)
		PUSH (fisrt_term / second_term);
	    cpu->pc += sizeof (unsigned char);
	},
	NO_ARGS
)

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

DEF_COMMAND (MUL, 0, "mul", 
	{
		CHECK_STACK_SIZE (cpu, cpu->stack.size, 2)
		arg_t fisrt_term = STACK_DATA_POISON;
		arg_t second_term = STACK_DATA_POISON;
		int stack_code1 = POP (&fisrt_term);
		int stack_code2 = POP (&second_term);
		CHECK_STACK (cpu, stack_code1)
		CHECK_STACK (cpu, stack_code2)
		PUSH (fisrt_term * second_term);
	    cpu->pc += sizeof (unsigned char);
	},
	NO_ARGS
)

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

DEF_COMMAND (OUT, 0, "out",
	{
		CHECK_STACK_SIZE (cpu, cpu->stack.size, 1)
		arg_t element = STACK_DATA_POISON;
		int stack_code = POP (&element);
		CHECK_STACK (cpu, stack_code)
		printf ("%lg\n", element);
	    cpu->pc += sizeof (unsigned char);
	},
	NO_ARGS
)

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

DEF_COMMAND (IN, 0, "in",
	{
		arg_t element = STACK_DATA_POISON;
		scanf ("%lg", &element);
		int stack_code = PUSH (element);
		CHECK_STACK (cpu, stack_code)
	    cpu->pc += sizeof (unsigned char);
	},
	NO_ARGS
)

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

DEF_COMMAND (DUMP, 0, "dump",
	{
	    CpuDump (cpu, stdout);
	    cpu->pc += sizeof (unsigned char);
	},
	NO_ARGS
)

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

DEF_COMMAND (DUMP_STK, 0, "dumpstk",
	{
	    StackDump (&cpu->stack, stdout); 
	    cpu->pc += sizeof (unsigned char);
	},
	NO_ARGS
)

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

DEF_COMMAND (VALIDATE, 0, "validate", 
  	{
	    StackValidate (&cpu->stack, STACK_EXTERNAL_FUNC_CODE);
	    cpu->pc += sizeof (unsigned char);
	},
	NO_ARGS
)

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

#ifdef DEF_COMMAND
#undef DEF_COMMAND
#endif