#!/bin/bash

while read RIGA; do
	echo "${RIGA%% *}" 1>&2;
	echo evviva;
done;
