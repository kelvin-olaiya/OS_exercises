#!/bin/bash
RIGHE_PARI=0
RIGHE_DISPARI=0

if (( $# > 9 )); then
    echo "Troppi argomenti"
fi;

for (( i = 1; i <= $# ; i = i + 1)); do
    RIGHE=`cat ${!i} | wc -l`
    if (( i % 2 == 0 )); then
        (( RIGHE_DISPARI = RIGHE_DISPARI + RIGHE ))
    else
        (( RIGHE_PARI = RIGHE_PARI + RIGHE ))
    fi;
done;

echo "Righe indice pari $RIGHE_PARI"
echo "Righe indice dispari $RIGHE_DISPARI" >&2