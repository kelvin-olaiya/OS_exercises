CFLAGS=-ansi -Wall -Wpedantic -pedantic

all: main.exe

main.exe: main.o quadrato.o dimezza.o
	gcc ${CFLAGS} -o main.exe main.o quadrato.o dimezza.o -lm

main.o: main.c quadrato.h dimezza.h
	gcc -c ${CFLAGS} main.c

quadrato.o: quadrato.c quadrato.h
	gcc -c ${CFLAGS} quadrato.c

dimezza.o: dimezza.c dimezza.h
	gcc -c ${CFLAGS} dimezza.c

.PHONY: clean

clean:
	-rm main.exe *.o
