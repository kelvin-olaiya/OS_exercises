#!/bin/bash

exec {FD}< /usr/include/stdio.h

while read -u ${FD} A B C D; do
	echo ${C};
done;

exec {FD}>&-
