#!/bin/bash

for NAME in `ls -d /usr/include/?[c-g]*`; do
 	if [[ ${#NAME} -lt 18 || ${#NAME} -gt 23 ]]; then
		echo ${NAME};
	fi;
done;
