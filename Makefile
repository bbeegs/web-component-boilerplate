CC=gcc
CFLAGS=-Wall -g

all: comp-gen clean

comp-gen: main.c compgen.o
	$(CC) -o comp-gen main.c compgen.o $(CFLAGS)

compgen.o: compgen.c
	$(CC) -c compgen.c $(CFLAGS)
clean:
	rm *.o
