# Makefile per con_trucco.c
# a causa della presenza di pthread
# occorre compilare col flag -D_REENTRANT
# oppure con  -D_THREAD_SAFE
# oppure con  -D_THREAD_SAFE
# per usare strerror_r devo anche usare _POSIX_C_SOURCE=200112L

CFLAGS=-ansi -Wpedantic -Wall -D_THREAD_SAFE -D_REENTRANT -D_POSIX_C_SOURCE=200112L
LIBRARIES=-lpthread

all: 	main.exe

main.exe: es0_premortem.o
	gcc ${CFLAGS} -o main.exe es0_premortem.o ${LIBRARIES}

es0_premortem.o: es0_premortem.c
	gcc ${CFLAGS} -c es0_premortem.c


.PHONY:	clean

clean:
	-rm -f *.exe *.o

