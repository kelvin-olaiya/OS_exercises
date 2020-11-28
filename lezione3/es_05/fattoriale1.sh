#!/bin/bash

if [[ $1 -ge 1 ]]; then
	((RIS = $RIS * $1));
	source ./fattoriale1.sh $(($1 - 1));
fi;
