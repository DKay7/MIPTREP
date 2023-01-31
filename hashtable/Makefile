CC=g++
CFLAGS=-Wall -Wextra -ggdb3 -Ofast
DBFLAGS=-g -ggdb3 -O0 -std=c++14 -Wall -Wextra -Weffc++ -Waggressive-loop-optimizations -Wc++0x-compat -Wc++11-compat -Wc++14-compat -Wcast-align -Wcast-qual -Wchar-subscripts -Wconditionally-supported -Wconversion -Wctor-dtor-privacy -Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security -Wformat-signedness -Wformat=2 -Winline -Wlarger-than=32542 -Wlogical-op -Wnon-virtual-dtor -Wopenmp-simd -Woverloaded-virtual -Wpacked -Wpointer-arith -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstack-usage=8192 -Wstric t-null-sentinel -Wstrict-overflow=2 -Wsuggest-attribute=noreturn -Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override -Wswitch-default -Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code -Wunused -Wuseless-cast -Wvariadic-macros -Wno-literal-suffix -Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast -Wno-varargs -fcheck-new -fsized-deallocation -fstack-protector -fstrict-overflow -flto-odr-type-merging -fno-omit-frame-pointer -fPIE -fsanitize=address  -fsanitize=bool -fsanitize=bounds -fsanitize=enum -fsanitize=float-cast-overflow -fsanitize=float-divide-by-zero -fsanitize=integer-divide-by-zero -fsanitize=leak -fsanitize=nonnull-attribute -fsanitize=null -fsanitize=object-size -fsanitize=return -fsanitize=returns-nonnull-attribute -fsanitize=shift -fsanitize=signed-integer-overflow -fsanitize=unreachable -fsanitize=vla-bound -fsanitize=vptr 
FASTFLAGS= -Ofast $(CFLAGS) -std=c++14

SOURCES=main.cpp default_hash_functions.cpp
INCLUDE=./libs/
EXECUTABLE=main



all: $(SOURCES)
	$(CC) $(SOURCES) $(CFLAGS) -I$(INCLUDE) -o $(EXECUTABLE)

fast: $(SOURCES)
		$(CC) $(SOURCES) $(CFLAGS) I$(INCLUDE) $(FASTFLAGS) -o $(EXECUTABLE)
		./$(EXECUTABLE)
	
db: $(SOURCES)
		$(CC) $(SOURCES) $(DBFLAGS) I$(INCLUDE) -o $(EXECUTABLE)
		./$(EXECUTABLE)