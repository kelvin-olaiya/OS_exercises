#!/bin/bash

if (($1 != 1)); then
	((RES=${RES}*$1))
	source ./fattoriale1.sh $(($1 - 1));
fi;
if (($1 == 1)); then
	echo $RES
fi;
