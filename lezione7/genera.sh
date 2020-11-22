#!/bin/bash

if [[ -z $1 ]]; then
	echo "Manca il file"
	exit 1;
fi;

echo `./random09.sh` >> $1 
