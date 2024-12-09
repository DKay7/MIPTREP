CC=g++
CFLAGS=-Wall -Wextra
DBFLAGS=-g -D NDEBUG -ggdb3 -O0 -std=c++14 -Wall -Wextra -Weffc++ -Waggressive-loop-optimizations -Wc++0x-compat -Wc++11-compat -Wc++14-compat -Wcast-align -Wcast-qual -Wchar-subscripts -Wconditionally-supported -Wconversion -Wctor-dtor-privacy -Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security -Wformat-signedness -Wformat=2 -Winline -Wlarger-than=32542 -Wlogical-op -Wnon-virtual-dtor -Wopenmp-simd -Woverloaded-virtual -Wpacked -Wpointer-arith -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstack-usage=8192 -Wstrict-null-sentinel -Wstrict-overflow=2 -Wsuggest-attribute=noreturn -Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override -Wswitch-default -Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code -Wunused -Wuseless-cast -Wvariadic-macros -Wno-literal-suffix -Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast -Wno-varargs -fcheck-new -fsized-deallocation -fstack-check -fstack-protector -fstrict-overflow -flto-odr-type-merging -fno-omit-frame-pointer -fPIE -fsanitize=address  -fsanitize=bool -fsanitize=bounds -fsanitize=enum -fsanitize=float-cast-overflow -fsanitize=float-divide-by-zero -fsanitize=integer-divide-by-zero -fsanitize=leak -fsanitize=nonnull-attribute -fsanitize=null -fsanitize=object-size -fsanitize=return -fsanitize=returns-nonnull-attribute -fsanitize=shift -fsanitize=signed-integer-overflow -fsanitize=unreachable -fsanitize=vla-bound -fsanitize=vptr 
FASTFLAGS= -O3 $(CFLAGS) -std=c++14

SOURCES_ASM= libs/stack/stack.cpp libs/text_lib/texlib.cpp libs/bin_text_lib/binlib.cpp assembler/asm.cpp assembler/asm_main.cpp

SOURCES_CPU= libs/stack/stack.cpp libs/text_lib/texlib.cpp libs/bin_text_lib/binlib.cpp machine/cpu.cpp machine/cpu_main.cpp

SOURCES_DISASM= libs/stack/stack.cpp libs/text_lib/texlib.cpp libs/bin_text_lib/binlib.cpp disassembler/disasm.cpp disassembler/disasm_main.cpp

EXECUTABLE_ASM=acc
EXECUTABLE_CPU=exec
EXECUTABLE_DISASM=disacc



all: $(SOURCES_ASM) $(EXECUTABLE_CPU) $(EXECUTABLE_DISASM) $(EXECUTABLE_ASM)  $(EXECUTABLE_CPU)  $(EXECUTABLE_DISASM)

$(EXECUTABLE_ASM): $(SOURCES_ASM)
	$(CC) $(SOURCES_ASM)   $(FASTFLAGS) -o $(EXECUTABLE_ASM)

$(EXECUTABLE_CPU): $(SOURCES_CPU)
	$(CC) $(SOURCES_CPU) $(FASTFLAGS) -o $(EXECUTABLE_CPU)
	
$(EXECUTABLE_DISASM): $(SOURCES_DISASM)
	$(CC) $(SOURCES_DISASM)  $(FASTFLAGS) -o $(EXECUTABLE_DISASM)
	

db: $(SOURCES_ASM) $(SOURCES_CPU) $(SOURCES_DISASM)
	$(CC) $(SOURCES_ASM) $(SOURCES_CPU) $(SOURCES_DISASM) $(DBFLAGS) $(CFLAGS) -o $@

create_docs:
	doxygen docs/doxy_config