CC=gcc
CFLAGS=-Wall -g

main: main.c compgen.o
	$(CC) -o main main.c compgen.o $(CFLAGS)

compgen.o: compgen.c
	$(CC) -c compgen.c $(CFLAGS)
clean:
	rm main *.o;
