CFLAGS=-ansi -Wpedantic -Wall -pedantic

all:	main.exe

main.exe:	main.o A.o
		gcc ${CFLAGS} -o main.exe main.o A.o -lm

main.o:		main.c A.h def.h A.o
		gcc -c ${CFLAGS} main.c

A.o:		A.c A.h def.h
		gcc -c ${CFLAGS} A.c def.h

.PHONY:		clean

clean:	
		rm -f main.exe main.o A.o

