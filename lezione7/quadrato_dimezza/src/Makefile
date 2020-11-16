CFLAGS=-ansi -Wall -Wpedantic -pedantic
INCLUDEDIR=../include
all: main.exe

main.exe: main.o quadrato.o dimezza.o
	gcc ${CFLAGS} -o main.exe main.o quadrato.o dimezza.o -lm

main.o: main.c ${INCLUDEDIR}/quadrato.h ${INCLUDEDIR}/dimezza.h
	gcc -c ${CFLAGS} -I${INCLUDEDIR} main.c

quadrato.o: quadrato.c
	gcc -c ${CFLAGS} quadrato.c

dimezza.o: dimezza.c
	gcc -c ${CFLAGS} dimezza.c

.PHONY: clean

clean:
	-rm main.exe *.o
