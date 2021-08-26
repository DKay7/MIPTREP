CC=g++
CFLAGS=-Wall -Wextra
SOURCES=solver.c main.c
DEBUG_SOURCES=unit_test.c
EXECUTABLE=solver

# коспилить не все
all: $(SOURCES)
	$(CC) $(SOURCES) $(CFLAGS) -o $(EXECUTABLE)

run: $(SOURCES)
	$(CC) $(SOURCES) $(CFLAGS) -o $(EXECUTABLE)
	./$(EXECUTABLE)

debug: $(SOURCES)
	$(CC) $(SOURCES) $(DEBUG_SOURCES) $(CFLAGS) -o $(EXECUTABLE) -D_DEBUG
	./$(EXECUTABLE)

create_docs:
	doxygen docs/doxy_config