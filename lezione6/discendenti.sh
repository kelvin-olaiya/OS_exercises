#!/bin/bash
PIDS=

if [[ $1 -gt 0 ]]; then
	for (( i=1; $i <= $1; i=$i+1 )); do
		./discendenti.sh $(($1 - 1)) &
		PIDS="$PIDS $!"
	done;
	wait $PIDS
fi;
echo $1
exit 0;
