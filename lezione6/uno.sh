#!/bin/bash

ricevutoSIGUSR2() {
	if read RIGA; then
		echo "UNO $RIGA"
		kill -SIGUSR2 $DUE_PID
	else
		exit 0;

	fi;
}

trap ricevutoSIGUSR2 SIGUSR2

echo ${BASHPID} > uno.pid.txt
sleep 2

read DUE_PID < due.pid.txt
ricevutoSIGUSR2

while true; do
sleep 1;
done;
