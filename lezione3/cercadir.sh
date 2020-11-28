#!/bin/bash
DIRECTORYNAME=/usr/include/
for NAME in `ls /usr/include`; do
	if [[ -e ${DIRECTORYNAME}${NAME} \
		&& -r ${DIRECTORYNAME}${NAME} \
		&& ( ${DIRECTORYNAME}${NAME} -nt /usr/include/stdio.h ) ]]; then
			echo ${DIRECTORYNAME}${NAME};
	fi;
done;
