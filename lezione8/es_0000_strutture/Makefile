SHELL = /bin/bash
CFLAGS = -ansi -Wpedantic -Wall -pedantic -D_POSIX_C_SOURCE=200112L -D_THREAD_SAFE -D_REENTRANT
LIBRARIES = -lpthread

all: main.exe

main.exe: main.o
	gcc ${CFLAGS} -o main.exe main.o ${LIBRARIES}

main.o: main.c
	gcc -c ${CFLAGS} -o main.o main.c ${CDEFINE}

.PHONY: clean

clean:
	-rm *.exe *.o