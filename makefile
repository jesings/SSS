all: sieve.o main.o
	gcc sieve.o main.o -o main -lm -Os
sieve.o: sieve.c
	gcc -c sieve.c
main.o: main.c
	gcc -c main.c
