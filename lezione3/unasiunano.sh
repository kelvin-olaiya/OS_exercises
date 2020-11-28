#!/bin/bash

COUNT=1
while read RIGA; do
	if (( $COUNT % 2 != 0 )); then
		echo $RIGA;
	fi;
	((COUNT=${COUNT}+1))
done;
