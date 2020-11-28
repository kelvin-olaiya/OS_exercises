#!/bin/bash
[[ -e 7.txt ]] && rm 7.txt;
[[ -e 8.txt ]] && rm 8.txt;

touch 7.txt 8.txt;

./leggi7.sh 2> /dev/null &
./leggi8.sh 2> /dev/null &
./strippa1.sh
