# Processor emulator

## Description

Given program main purpose is to emulate computer processor.

It includes three main parts:

1. Assembler, which compiles *.asm [assembler] file to *.mc [machine commands] file.
2. CPU, which executes *.mc file
3. Disassembler, which decompiles *.mc file back to *.asm file.

## Getting started

**First of all, clone this repo to your local PC with:**

`git clone https://github.com/DKay7/MIPTREP.git /your/local/directory/`

---

**Go to project's directory and make executable files through run**

`make`

---

**To compile any \*.asm file you want, run the following command:**

`./acc path_to_asm_file.asm [path_to_output_file.mc] [path_to_listig_file.lst]` 

*Note:* args in "[" "]" are optional.

---

**To execute comiled programm, run:**

`./exec path_to_file.mc`

---

**To decompile programm, run:**

`./disasm path_to_file.mc path_to_output_file.asm`

---

For example: 
To compile square_solver example run:

`./acc /examples/square_solver/square_solver.asm`

Then, to execute it, run:

`./exec /examples/square_solver/square_solver.mc`

Also, you can simply decompile it by running:

`./disasm /examples/square_solver/square_solver.mc`

---

**Also, there is img-to-videoram translator. You can run it with any image you want by the following commad**

`python3 /examples/ascii_generator.py`

Then enter path to image file and width in ascii-symols (150 is the best for most of pictures)

Wait for some time and search for *.asm file in the directory. Filename should be the same as the picture filename.

After that, you can compile and execute taken *.asm file and see the picture in processor video-ram.

Some of such *.asm files are available in /examples/vram/ subdir.

---

## For those who dare

### How does it work

Cpu includes:
1. Stack data structure
2. Registers
3. Random Access Memory, RAM
4. Video Random Access Memory, V-RAM

Stack is just LIFO data structure. In this cpu it stroes data of double type. Stack has no fixed size it can do both: increase and decrease depends on its capacity.

Registers is just fast-acess memory blocks, one register can hold just one value, also of double type. Total num of registers is 24.

RAM is as Random Acess Memory, in real CPUs it way much slower than registers, but in this realisation speeds of acess to registers and to the RAM are correlated.

VRAM is just a part of RAM, which data is interpreted by cpu as ascii-characters. You can set the place where VRAM starts at RAM,how long shoud it be and print out VRAM data to the screen by some of the commands below. 

--- 

### List of available commands

1. `push value` -- pushes value to stack. 

    Available options: 

    1.1 `push reg_name` -- pushes value from register

    1.2 `push [value]` -- pushes value from ram element, which is pointed by value. 
    
    1.3 `push [reg_name]` -- same as above, but pointer stores in register.

2. `pop` -- pops value out of stack

    Available options: 

    1.1 `pop reg_name` -- pops value to register
    
    1.2 `pop [value]` -- pops value to ram element, which is pointed by value. 
    
    1.3 `pop [reg_name]` -- same as above, but pointer stores in register.

3. `jmp label_name` -- unconditional jump to label

4. `je label_name` -- jump if two elements in stack are equal

5. `jne label_name` -- jump if two elements in stack are not equal

6. `ja label_name` -- jump if one element in stack are above than another

7. `jae label_name` -- jump if one element in stack are above or equal than another

8. `jb label_name` -- jump if one element in stack are below than another

9. `jbe label_name` -- jump if one element in stack are below or equal than another

10. `call func_name` -- calls a function.

11. `ret` -- pops addres from stack and returns from function.

12. `vrsetx value` -- sets screen width.

13. `vrsety value` -- sets screen height.

14. `scrupd` -- updates screen (redraws it).

15. `scrclr` -- clears screen buffer (not the screen).

16. `clrbuf value` -- clears ram from 0 to given value.

17. `add` -- adding two values from stack and pushes result back.

18. `sub` -- substracts two values from stack and pushes result back.

19. `mul` -- multiplies two values from stack and pushes result back.

20. `div` -- divides two values from stack and pushes result back.

21. `sqrt` -- count square root for value from stack and pushes result back.

22. `sin` -- count sine root for value from stack and pushes result back.

23. `cos` -- count cosine root for value from stack and pushes result back.

24. `rnd` -- floorly rounds value from stack and pushes result back.

25. `in` -- takes value from the user and pushes it to the stack.

26. `out` -- pops value from the stack and show it to the user.

27. `dump` -- dumps info about cpu.

28. `dumpstk` -- dumps info about cpu's stack.

29. `validate` -- validates cpu's stack.

30. `hlt` -- terminates program.

---

### How to add new command / register / error type

All processor commands, register and error are written on Domain-specific language (DSL). You can easily add new command by writing new command-definition to defines_and_setups/command_defenitions.h. New error-types and registers could be added by the same way. Don't forget to increase (decrease) number of used registers in cpu_setup.

Have a good luck!