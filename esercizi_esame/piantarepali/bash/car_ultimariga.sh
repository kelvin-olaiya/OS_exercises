#!/bin/bash

for file in `find /usr/include/linux/ -name "*f*.h" -maxdepth 1`; do
    NUM_RIGHE=`cat $file | wc -l`

    if [[ $NUM_RIGHE -ge 10 ]] && [[ $NUM_RIGHE -le 100 ]]; then
        echo `tail -n 1 $file | wc -m`
    fi;
done;