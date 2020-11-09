#!/bin/bash

trap ricevutoSIGUSR2 SIGUSR2

ricevutoSIGUSR2() {
	read RIGA
	if [[ $? -ne 0 ]]; then
		exit 0;
	fi;

	echo "DUE $RIGA"
	kill -SIGUSR2 $UNO_PID
}

echo $BASHPID > due.pid.txt
sleep 2

read UNO_PID < uno.pid.txt

while true; do
sleep 1
done;
