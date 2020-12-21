SHELL = /bin/bash
CFLAGS = -ansi -Wall -Wpedantic -pedantic
CDEFINE = -D_POSIX_C_SOURCE=200112L -D_THREAD_SAFE -D_REENTRANT
CLIBRARIES = -lpthread

all: vacche.exe

vacche.exe: vacche.o DBGpthread.o
	gcc ${CFLAGS} -o vacche.exe vacche.o DBGpthread.o ${CLIBRARIES}

vacche.o: vacche.c
	gcc -c ${CFLAGS} ${CDEFINE} -o vacche.o vacche.c 

DBGpthread.o: DBGpthread.c DBGpthread.h printerror.h
	gcc -c ${CFLAGS} ${CDEFINE} -o DBGpthread.o DBGpthread.c

.PHONY: clean

clean:
	rm -f *.exe *.o