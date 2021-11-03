#ifndef DEF_COMMAND
#define DEF_COMMAND(...)
#endif

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

// Optional and required arguments.
// Figured out by high bit (1 -- required, 0 -- optional)
#define ARG(    number, type)  ((0x10 | (type)) >> (number * 4))
#define OPT_ARG(number, type)  ((0x00 | (type)) >> (number * 4))
#define NO_ARGS                (0x0)
#define ARG_MASK                0xF0

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

#define PUSH(arg)	StackPush (&cpu->stack, (arg))
#define POP(adr)	StackPop (&cpu->stack, (adr))

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

// name, n_args, str_name, cmd_realization

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
// MAIN FUNCTIONS BLOCK
//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

DEF_COMMAND (HLT, 0, "hlt",
	{
		return cpu->errno;
	}, 
	NO_ARGS
)

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

DEF_COMMAND (PUSH, 1, "push",
	{	
		arg_t* value =  CpuGetArgument (cpu);
		PUSH (*value);
	    cpu->pc += sizeof (unsigned char);
	}, 
	ARG (0, (RAM_VALUE | REGISTER_VALUE | IMMEDIATE_CONST))
)

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

DEF_COMMAND (POP, 1, "pop",
	{	
		arg_t* value =  CpuGetArgument (cpu);

		if (!value)
		{	
			// no args
			arg_t val = 0;
			POP (&val);
		}
		
		else
		{
			POP (value);
		}

	    cpu->pc += sizeof (unsigned char);
	},
	OPT_ARG (0, (RAM_VALUE | REGISTER_VALUE))
)

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
// JUMPS & CALLS BLOCK
//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

DEF_COMMAND (JMP, 1, "jmp",
	{
		arg_t* new_pc = CpuGetArgument (cpu);
		cpu->pc = (unsigned long) (*new_pc);
	},
	ARG (0, (IMMEDIATE_CONST))
)

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

DEF_COMMAND (JEQ, 1, "je",
	{	
		arg_t first_term = STACK_DATA_POISON;
		arg_t second_term = STACK_DATA_POISON;
		POP (&first_term);
		POP (&second_term);
		arg_t* new_pc = CpuGetArgument (cpu);

		if (fabs (first_term - second_term) <= EPSILON)
		{			
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

DEF_COMMAND (JNE, 1, "jne",
	{	
		arg_t first_term = STACK_DATA_POISON;
		arg_t second_term = STACK_DATA_POISON;
		POP (&first_term);
		POP (&second_term);
		arg_t* new_pc = CpuGetArgument (cpu);

		if (fabs (first_term - second_term) > EPSILON)
		{			
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
		arg_t first_term = STACK_DATA_POISON;
		arg_t second_term = STACK_DATA_POISON;
		POP (&first_term);
		POP (&second_term);
		arg_t* new_pc = CpuGetArgument (cpu);

		if (second_term > first_term)
		{			
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
		arg_t first_term = STACK_DATA_POISON;
		arg_t second_term = STACK_DATA_POISON;
		POP (&first_term);
		POP (&second_term);
		arg_t* new_pc = CpuGetArgument (cpu);

		if (second_term >= first_term)
		{			
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
		arg_t first_term = STACK_DATA_POISON;
		arg_t second_term = STACK_DATA_POISON;
		POP (&first_term);
		POP (&second_term);
		arg_t* new_pc = CpuGetArgument (cpu);

		if (second_term < first_term)
		{			
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
		arg_t first_term = STACK_DATA_POISON;
		arg_t second_term = STACK_DATA_POISON;
		POP (&first_term);
		POP (&second_term);
		arg_t* new_pc = CpuGetArgument (cpu);

		if (second_term <= first_term)
		{			
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
		cpu->pc = ((unsigned long) (*new_pc));

	},
	ARG (0, (IMMEDIATE_CONST))
)

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

DEF_COMMAND (RET, 0, "ret",
	{	
		arg_t new_pc = -1;
		int stack_code = POP (&new_pc);

		cpu->pc = ((unsigned long) (new_pc));
	},
	NO_ARGS
)

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
// VRAM BLOCK
//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

DEF_COMMAND (VRSETX, 1, "vrsetx",
	{	
		arg_t* vr_x_size = CpuGetArgument (cpu);
		cpu->vr.size_x = *(vr_x_size);
	    cpu->pc += sizeof (unsigned char);		
	},
	ARG (0, (RAM_VALUE | REGISTER_VALUE | IMMEDIATE_CONST))
)

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

DEF_COMMAND (VRSETY, 1, "vrsety",
	{	
		arg_t* vr_y_size = CpuGetArgument (cpu);
		cpu->vr.size_y = *(vr_y_size);
	    cpu->pc += sizeof (unsigned char);		
	},
	ARG (0, (RAM_VALUE | REGISTER_VALUE | IMMEDIATE_CONST))
)

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

DEF_COMMAND (VRSETSTART, 1, "vrsetstart",
	{	
		arg_t* vr_start_ptr = CpuGetArgument (cpu);
		cpu->vr.start_ptr = *(vr_start_ptr);
	    cpu->pc += sizeof (unsigned char);		
	},
	ARG (0, (RAM_VALUE | REGISTER_VALUE | IMMEDIATE_CONST))
)


//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

// DEF_COMMAND (DELAY, 0, "delay",
// 	{	
// 		usleep (1000);
// 	    cpu->pc += sizeof (unsigned char);		
// 	},
// 	NO_ARGS
// )

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

DEF_COMMAND (SCRUPD, 0, "scrupd",
	{	
		printf ("\x1b[H");

		for (size_t y = 0; y < cpu->vr.size_y; ++y)
		{		
			size_t y_shift = y * cpu->vr.size_x;

			for (size_t x = 0; x < cpu->vr.size_x; ++x)
			{	
				int symbol = cpu->ram [cpu->vr.start_ptr + y_shift + x];
				
				if (symbol == 0 || symbol == '\n')
                	putchar (' ');
				
				else
					putchar (symbol);
			}
			putchar ('\n');
		}

		printf ("\x1b[2J");

	    cpu->pc += sizeof (unsigned char);		
	},
	NO_ARGS
)


//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

DEF_COMMAND (SCRCLR, 0, "scrclr",
	{	
		memset (cpu->ram + cpu->vr.start_ptr, 0, sizeof (arg_t) * cpu->vr.size_x * cpu->vr.size_y);
	    cpu->pc += sizeof (unsigned char);		
	},
	NO_ARGS
)

DEF_COMMAND (CLRBUF, 1, "clrbuf",
	{	
		arg_t* clear_size = CpuGetArgument (cpu);
		memset (cpu->ram, 0, sizeof (arg_t) * (*clear_size));
	    cpu->pc += sizeof (unsigned char);
	},
	ARG (0, (IMMEDIATE_CONST))
)

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
// MATH BLOCK
//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

DEF_COMMAND (ADD, 0, "add",
	{
		arg_t first_term = STACK_DATA_POISON;
		arg_t second_term = STACK_DATA_POISON;
		POP (&first_term);
		POP (&second_term);
		PUSH (first_term + second_term);
	    cpu->pc += sizeof (unsigned char);
	},
	NO_ARGS
)

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

DEF_COMMAND (SUB, 0, "sub", 
	{
		arg_t first_term = STACK_DATA_POISON;
		arg_t second_term = STACK_DATA_POISON;
		POP (&first_term);
		POP (&second_term);
		PUSH (second_term - first_term);
	    cpu->pc += sizeof (unsigned char);
	},
	NO_ARGS
)	

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

DEF_COMMAND (DIV, 0, "div", 
	{
		arg_t first_term = STACK_DATA_POISON;
		arg_t second_term = STACK_DATA_POISON;
		POP (&first_term);
		POP (&second_term);
		// CHECK_ZERO_DIVISION (cpu, first_term)
		PUSH (second_term / first_term);
	    cpu->pc += sizeof (unsigned char);
	},
	NO_ARGS
)

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

DEF_COMMAND (MUL, 0, "mul", 
	{
		arg_t first_term = STACK_DATA_POISON;
		arg_t second_term = STACK_DATA_POISON;
		POP (&first_term);
		POP (&second_term);
		PUSH (first_term * second_term);
	    cpu->pc += sizeof (unsigned char);
	},
	NO_ARGS
)

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

DEF_COMMAND (SQRT, 0, "sqrt", 
	{
		arg_t term = STACK_DATA_POISON;
		POP (&term);
		PUSH (sqrt (term));
	    cpu->pc += sizeof (unsigned char);
	},
	NO_ARGS
)

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

DEF_COMMAND (SIN, 0, "sin", 
	{
		arg_t term = STACK_DATA_POISON;
		POP (&term);
		PUSH (sin (term));
	    cpu->pc += sizeof (unsigned char);
	},
	NO_ARGS
)

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

DEF_COMMAND (COS, 0, "cos", 
	{
		arg_t term = STACK_DATA_POISON;
		POP (&term);
		PUSH (cos (term));
	    cpu->pc += sizeof (unsigned char);
	},
	NO_ARGS
)


//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

DEF_COMMAND (RND, 0, "rnd", 
	{
		arg_t term = STACK_DATA_POISON;
		POP (&term);
		PUSH ((int) term);
	    cpu->pc += sizeof (unsigned char);
	},
	NO_ARGS
)

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
// IO BLOCK
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
// DUMPS BLOCK
//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

DEF_COMMAND (DUMP, 0, "dump",
	{	
		FILE* f = fopen ("dump.lst", "w");
	    CpuDump (cpu, f);
	    cpu->pc += sizeof (unsigned char);
		fclose (f);
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