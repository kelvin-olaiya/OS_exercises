#!/bin/bash

if [[ ${#1} == 0 || ${#2} == 0 ]]; then
	echo "I 2 file di input!!"
	exit
fi;

exec {FD1}< $1
exec {FD2}< $2
CURRENT=$FD1
while read -u $CURRENT RIGA; RIS=$?; [[ $RIGA != "" || $RIS -eq 0 ]]; do
	echo $RIGA
	if (($CURRENT == $FD1 )); then
		CURRENT=$FD2
	elif (( $CURRENT == $FD2 )); then
		CURRENT=$FD1
	fi;
done > out.txt;

if (($CURRENT == $FD1 )); then
	CURRENT=$FD2
elif (( $CURRENT == $FD2 )); then
	CURRENT=$FD1
fi;

while read -u $CURRENT RIGA; do
	echo $RIGA
done >> out.txt;
