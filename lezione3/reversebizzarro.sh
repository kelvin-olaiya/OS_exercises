#!/bin/bash

STRINGA=$1
REVSTRING=

while [[ ${#STRINGA} -gt 0 ]]; do
	REVSTRING=${REVSTRING}`echo $STRINGA | cut -b ${#STRINGA}-`
	if [[ $(( ${#STRINGA} - 1 )) -gt 0 ]]; then
		 STRINGA=`echo $STRINGA | cut -b 1-$(( ${#STRINGA} - 1 ))`
	else
		STRINGA=
	fi;
done;

echo $REVSTRING
