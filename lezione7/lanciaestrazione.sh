#!/bin/bash

./estraiasterischi.sh < input.txt &
PID_ESTRAI=$!
echo "fatto" &
wait $PID_ESTRAI
