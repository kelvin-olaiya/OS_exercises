#!/bin/bash

if (( $1 < 0 )); then
	echo "E necessario un intero positivo"
	exit 1;
fi;

NUM=1;
while (( NUM <= $1 )); do
	sleep 1;
	echo -n ".$BASHPID";
	((NUM=NUM+1))
done;

echo ""

