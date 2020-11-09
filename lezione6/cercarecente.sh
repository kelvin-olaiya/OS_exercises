#!/bin/bash

recente=

for file in `find /usr/include/linux -mindepth 2 -type f -name *.h`; do
	if [[ -z $appoggio ]]; then
		recente=$file
	fi;
	if [[ $file -nt $appoggio ]]; then
		recente=$file
	fi;
done;
echo $recente


