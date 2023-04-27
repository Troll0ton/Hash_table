compile: main.cpp
	gcc -O2 -c -mavx -mavx512dq main.cpp hash_table.cpp hash_functions.cpp input_utils.cpp text_utils.cpp
	nasm -f elf64 -g hash_function_asm.s -o hash_function_asm.o
	gcc -no-pie main.o hash_table.o hash_functions.o input_utils.o text_utils.o hash_function_asm.o

run:
	./app