compile: main.cpp
	gcc -O2 -c -mavx -mavx512dq main.cpp hash_table.cpp hash_functions.cpp input_utils.cpp text_utils.cpp
	gcc main.o hash_table.o hash_functions.o input_utils.o text_utils.o

run:
	./app