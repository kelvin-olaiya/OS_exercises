SHELL = /bin/bash
CFLAGS = -ansi -Wall -Wpedantic -pedantic
CDEFINE = -D_POSIX_C_SOURCE=200112L -D_THREAD_SAFE -D_REENTRANT
CLIBRARIES = -lpthread

all: main.exe

main.exe: main.o DBGpthread.o
	gcc ${CFLAGS} -o main.exe main.o DBGpthread.o ${CLIBRARIES}

main.o: main.c
	gcc -c ${CFLAGS} ${CDEFINE} -o main.o main.c 

DBGpthread.o: DBGpthread.c DBGpthread.h printerror.h
	gcc -c ${CFLAGS} ${CDEFINE} -o DBGpthread.o DBGpthread.c

.PHONY: clean

clean:
	rm -f *.exe *.o