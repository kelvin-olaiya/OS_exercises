CFLAGS=-ansi -Wall -Wpedantic -pedantic

all: main.exe

main.exe: main.o
	gcc ${CFLAGS} -o main.exe main.o

main.o: main.c util.h
	gcc -c ${CFLAGS} -D'MEMORY_ALLOC(dest)=do{ dest = malloc(10 * sizeof(int32_t));if(dest != NULL){int j;for(j = 0; j < 10; j++){dest[j] = - 1000+j;}}} while(0)' main.c

.PHONY: clean

clean:
	-rm main.exe *.o
