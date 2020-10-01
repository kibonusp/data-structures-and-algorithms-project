CC=gcc
INCLUDES=./includes
SOURCES=./sources
BINARY=./a.out
PROG=./main.c
FLAGS=-Wall -Werror -g

all:
	@$(CC) $(PROG) $(SOURCES) -I$(INCLUDES) $(FLAGS)

valgrind:
	@valgrind --track-origins=yes --leak-check=full --show-leak-kinds=all $(BINARY)

run:
	@$(BINARY)

clean: 
	@rm -r *.o 

zip:
	zip -r sequential_list.zip Makefile ./includes/ ./sources/ ./main.c