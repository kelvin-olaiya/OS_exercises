#!/bin/bash

#leggo define.h

NUM=`grep NUM define.h | cut -d' ' -f 3`

(
	for (( i=1 ; $i <= $NUM ; i=$i + 1 )); do
		echo "int var${i} = $i;";
	done;
 	echo "int conta(void) {"
	echo "int somma = 0;"
	for (( i=1 ; $i <= $NUM ; i=$i + 1 )); do
		echo -e "	somma += var${i};"
	done;
	echo "	return somma;"
	echo "}"
) > variabiliglobali.c
