#!/bin/bash

if [[ -f out.txt ]]; then
	rm out.txt
fi;

SOMMA=0

for (( i=0; $i <= 9; i = $i+1 )); do
	./genera.sh out.txt
done;

while read NUM; do
	(( SOMMA = $SOMMA + $NUM ))
done < out.txt

echo $SOMMA
