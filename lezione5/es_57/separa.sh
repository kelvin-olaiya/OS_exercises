#!/bin/bash

RESIDUO=$PATH
PERCOSO=
while [[ $RESIDUO  != $PERCORSO ]]; do
	PERCORSO=${RESIDUO%%:*}
	echo $PERCORSO
	RESIDUO=${RESIDUO##${PERCORSO}:}
	sleep 1
done;

