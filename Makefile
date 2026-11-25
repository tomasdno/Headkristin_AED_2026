CC = gcc
CFLAGS = -Wall -std=c99 -O3

healkristin: Healkristin.o Unionfind.o
	$(CC) $(CFLAGS) -o healkristin Healkristin.o Unionfind.o -lm

Healkristin.o: Healkristin.c Healkristin.h Unionfind.h
	$(CC) $(CFLAGS) -c Healkristin.c

Unionfind.o: Unionfind.c Unionfind.h
	$(CC) $(CFLAGS) -c Unionfind.c

clean:
	rm -f healkristin *.o