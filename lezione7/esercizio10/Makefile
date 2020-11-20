CFLAGS = -ansi -Wall -Wpedantic -pedantic -Werror

all: casuale.exe

casuale.exe: casuale.o
	gcc ${CFLAGS} -o casuale.exe casuale.o
	
casuale.o: casuale.c
	gcc -c ${CFLAGS} -o casuale.o casuale.c
	
.PHONY: clean

clean:
	-rm casuale.exe casuale.o
