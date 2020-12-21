SHELL = /bin/bash
CFLAGS = -ansi -Wall -Wpedantic -pedantic
CDEFINE = -D_POSIX_C_SOURCE=200112L -D_THREAD_SAFE -D_REENTRANT
CLIBRARIES = -lpthread

all: main.exe

main.exe: pontepericolante_semplice.o DBGpthread.o
	gcc ${CFLAGS} -o main.exe pontepericolante_semplice.o DBGpthread.o ${CLIBRARIES}

pontepericolante_semplice.o: pontepericolante_semplice.c
	gcc -c ${CFLAGS} ${CDEFINE} -o pontepericolante_semplice.o pontepericolante_semplice.c 

DBGpthread.o: DBGpthread.c DBGpthread.h printerror.h
	gcc -c ${CFLAGS} ${CDEFINE} -o DBGpthread.o DBGpthread.c

.PHONY: clean

clean:
	rm -f *.exe *.o