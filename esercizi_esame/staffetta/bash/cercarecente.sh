#!/bin/bash
ESAMINATI=0
CONFRONTO=""
for percorso in `find /usr/include/linux -mindepth 2 -name "*.h"`; do
    if (( $ESAMINATI == 0 )); then
        (( ESAMINATI = $ESAMINATI + 1))
        CONFRONTO=$percorso
    else
        if [[ $percorso -nt $CONFRONTO ]]; then
            CONFRONTO=$percorso
        fi;
    fi;
done;

echo $CONFRONTO;

