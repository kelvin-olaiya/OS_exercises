#!/bin/bash
DIRECTORY="/usr/include/"
for NAME in `ls -d /usr/include/?[c-g]*`; do
	if [[ (${#FPATH} -lt 18 || ${#FPATH} -gt 23) ]]; then
		echo $NAME;
	fi;
done;
