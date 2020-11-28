#!/bin/bash

if [[ -e $1  ]]; then
	exec {FD}< $1
	OUT=
	while read -u $FD A B C ; do
		OUT=${OUT}${B}
	done;

	echo "OUT = $OUT"
	exit 0;
fi;
