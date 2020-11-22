#!/bin/bash

for percorso in `find /usr/include -mindepth 1 -type d`; do
	nome=${percorso##*/}
	if (( ${#nome} >= 7 )); then
		echo ${nome:6:1} >> 7.txt

		if (( ${#nome} >= 8 )); then
			echo ${nome:7:1} >> 8.txt
		fi;
	fi;
done;
