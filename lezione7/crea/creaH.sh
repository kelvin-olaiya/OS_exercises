#!/bin/bash

#leggo define.h

NUM=`grep NUM define.h | cut -d' ' -f 3`

(
	echo "#ifndef __VARIABILIGLOBALI_H__"
	echo "#define __VARIABILIGLOBALI_H__"
	for (( i=1 ; $i <= $NUM ; i=$i + 1 )); do
		echo "extern int var${i};";
	done;
 	echo "int conta(void);"
	echo "#endif"
) > variabiliglobali.h
