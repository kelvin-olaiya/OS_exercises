#!/bin/bash

sleep 2
TUTTO=
while read RIGA; do
	while true; do
		PAROLA="${RIGA%% *}"
		if [[ -n `echo "$PAROLA" | grep "*"` ]]; then
			TUTTO="$TUTTO$PAROLA "
		fi;
		if [[ "$PAROLA" ==  "$RIGA" ]]; then
			break;
		fi;
		RIGA="${RIGA#$PAROLA }"
	done;
done;

echo "$TUTTO"
