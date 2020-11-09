#!/bin/bash

while read NOME COGNOME MATRICOLA VOTO; do
	if [[ -z `grep "$NOME $COGNOME" RisultatiProvaPratica1.txt` ]]; then
		if ((  $VOTO < 18 )); then
			echo $COGNOME $MATRICOLA $NOME $COGNOME $VOTO
		fi;
	fi;
done < RisultatiProvaPratica2.txt | sort | cut -d ' ' -f2-;
