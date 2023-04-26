CC=g++
CFLAGS=-O2 -c -mavx -mavx512dq
LDFLAGS=
SOURCES=main.cpp hash_table.cpp hash_functions.cpp input_utils.cpp text_utils.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=app

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@