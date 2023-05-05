CC=g++
ASM=nasm

CFLAGS=-O2 -g -mavx -mavx512dq -Wall -c
AFLAGS=-f elf64 -g
IFLAGS=-no-pie

SOURCES=main.cpp hash_table.cpp hash_functions.cpp input_utils.cpp text_utils.cpp
OBJECTS=$(SOURCES:.cpp=.o)

ASMSRC=hash_function_asm.s
ASMOBJ=$(ASMSRC:.s=.o)

EXECUTABLE=app

all: $(SOURCES) $(ASMSRC) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) $(ASMOBJ)
	$(CC) $(IFLAGS) $(OBJECTS) $(ASMOBJ) -o $@

.cpp.o:
	$(CC) $(IFLAGS) $(CFLAGS) $< -o $@

.s.o:
	$(ASM) $(IFLAGS) $(AFLAGS) $< -o $@

clear:
	rm -rf *.o app