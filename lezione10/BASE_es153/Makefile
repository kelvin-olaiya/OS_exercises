SHELL = /bin/bash
CFLAGS = -ansi -Wall -Wpedantic -pedantic
CDEFINE = -D_POSIX_C_SOURCE=200112L -D_THREAD_SAFE -D_REENTRANT
CLIBRARIES = -lpthread

all: piattello.exe

piattello.exe: piattello.o DBGpthread.o
	gcc ${CFLAGS} -o piattello.exe piattello.o DBGpthread.o ${CLIBRARIES}

piattello.o: piattello.c
	gcc -c ${CFLAGS} ${CDEFINE} -o piattello.o piattello.c 

DBGpthread.o: DBGpthread.c DBGpthread.h printerror.h
	gcc -c ${CFLAGS} ${CDEFINE} -o DBGpthread.o DBGpthread.c

.PHONY: clean

clean:
	rm -f *.exe *.o