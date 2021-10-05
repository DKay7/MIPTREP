CC=g++
CFLAGS=-Wall -Wextra
SOURCES=main.cpp stack.cpp
EXECUTABLE=main

all: $(SOURCES)
	$(CC) $(SOURCES) $(CFLAGS) -o $(EXECUTABLE)

run: $(SOURCES)
	$(CC) $(SOURCES) $(CFLAGS) -o $(EXECUTABLE)
	./$(EXECUTABLE)

create_docs:
	doxygen docs/doxy_config