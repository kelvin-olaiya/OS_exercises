CFLAGS = -Wall -Wpedantic -ansi -pedantic
CSYM = -D_POSIX_C_SOURCE=200112L -D_THREAD_SAFE -D_REENTRANT
CLIB = -lpthread

all: main.exe

main.exe: main.o
	gcc ${CFLAGS} -o main.exe main.o ${CLIB}

main.o: main.c
	gcc -c ${CFLAGS} -o main.o main.c ${CSYM}

.PHONY: clean

clean:
	-rm *.exe *.o
