all: sieve.o main.o
	gcc sieve.o main.o -o main -lm
all2: sieve2.o main.o
	gcc sieve2.o main.o -o main -lm -lpthread
sieve.o: sieve.c
	gcc -c sieve.c
sieve2.o: sieve2.c
	gcc -c sieve2.c -O3
main.o: main.c
	gcc -c main.c -O3
