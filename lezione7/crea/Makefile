CFLAGS = -Wall -Wpedantic -ansi -pedantic

all: variabiliglobali.c variabiliglobali.h main.exe

main.exe: main.o variabiliglobali.o
	gcc ${CFLAGS} -o main.exe main.o variabiliglobali.o

main.o: main.c define.h
	gcc -c ${CFLAGS} -o main.o main.c

variabiliglobali.o: variabiliglobali.c
	gcc -c ${CFLAGS} -o variabiliglobali.o variabiliglobali.c

variabiliglobali.c: define.h
	./creaC.sh

variabiliglobali.h: define.h
	./creaH.sh

.PHONY: clean


clean:
	-rm variabiliglobali.* main.exe
