CFLAGS = -ansi -Wall -Wpedantic -Werror -pedantic

all: dammi_il_precedente.exe

dammi_il_precedente.exe: dammi_il_precedente.o
	gcc ${CFLAGS} -o dammi_il_precedente.exe dammi_il_precedente.o
	
dammi_il_precedente.o: dammi_il_precedente.c
	gcc -c ${CFLAGS} -o dammi_il_precedente.o dammi_il_precedente.c
	
.PHONY: clean

clean:
	-rm dammi_il_precedente.exe dammi_il_precedente.o
