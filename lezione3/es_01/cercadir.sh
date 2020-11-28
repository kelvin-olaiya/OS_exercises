#!/bin/bash
DIRECTORY="/usr/include/"
for NAME in `ls /usr/include/`; do
	if [[ -d ${DIRECTORY}${NAME} && -r ${DIRECTORY}$NAME && ${DIRECTORY}$name -nt "/usr/include/stdio.h" ]]; then
		echo "/usr/include/${NAME}";
	fi;
done;
