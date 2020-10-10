CC=gcc
INCLUDES=./includes
SOURCES=./sources/*.c
BINARY=./main
PROG=./main.c
FLAGS=-Wall -Werror -g

all:
	@$(CC) $(PROG) -o $(BINARY) $(SOURCES) -I$(INCLUDES) $(FLAGS)

valgrind:
	@valgrind --track-origins=yes --leak-check=full --show-leak-kinds=all $(BINARY)

run:
	@$(BINARY)

clean: 
	@rm -r *.o 

zip:
	zip -r Project_1.zip Makefile ./includes/ ./sources/ ./main.c