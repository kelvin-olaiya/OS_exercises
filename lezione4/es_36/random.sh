#!/bin/bash

COUNT=0

while [[ $((COUNT=$COUNT + 1)) && $(( $RANDOM % 10)) != 2 ]]; do
	echo "$RANDOM"
done;

echo "La variabile random e stata controllata $COUNT volte"
