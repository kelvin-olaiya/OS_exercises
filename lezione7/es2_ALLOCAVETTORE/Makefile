CFLAGS=-ansi -Wall -Wpedantic -pedantic

all: main.exe

main.exe: main.o
	gcc ${CFLAGS} -o main.exe main.o

main.o: main.c util.h
	gcc -c ${CFLAGS} main.c

.PHONY: clean

clean:
	-rm main.exe *.o
