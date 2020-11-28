#!/bin/bash

exec {FD}< miofileNoNL.txt

if (( $? == 0 )); then
	while read -u $FD RIGA; [[ $? == 0 || ${#RIGA} > 0 ]] ; do
		echo $RIGA;
	done;
fi;
