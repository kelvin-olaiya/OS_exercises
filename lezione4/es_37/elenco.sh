#!/bin/bash

LungNomiDirectory=0
NumFiles=0

for file in `ls ./`; do
	if [[ -f $file ]]; then
		((NumFiles=$NumFiles+1))
	elif [[ -d $file ]]; then
		((LungNomiDirectory=$LungNomiDirectory + ${#file} ))
	fi;
done;

echo "somma lungezza directory: $LungNomiDirectory, n. files: $NumFiles"
