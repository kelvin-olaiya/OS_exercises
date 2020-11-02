#!/bin/bash
PIDS=

for (( i=0; $i < 10; i = $i + 1)); do
	./puntini.sh 20 &
	PIDS="$PIDS "$!
done >&2 ;

echo $PIDS
