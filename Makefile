all: compile clean

compile: main.o pilha.o
	gcc -g -o programa main.o pilha.o -lm

pilha.o: pilha.c pilha.h
	gcc -g -c pilha.c

main.o: main.c
	gcc -g -c main.c

clean:
	rm -rf *.o
