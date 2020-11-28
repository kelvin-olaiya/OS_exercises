#!/bin/bash

exec {FD}< /usr/include/stdio.h
#mi chiedo se l'apertura e andata a buon fine
if (( $? == 0 )); then
	NUM=0
	while read -u $FD -N 1 -r C; do
		(( NUM = $NUM + 1 ));
	done;
	exec {FD}>&-
	echo $NUM;
fi;
echo "CONFERMA -->" `wc -m /usr/include/stdio.h`
