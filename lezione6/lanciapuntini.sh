#!/bin/bash

(sleep 5; ps | grep puntini.sh | read P_ID; echo "echo dice  $P_ID") &
./puntini.sh 30
