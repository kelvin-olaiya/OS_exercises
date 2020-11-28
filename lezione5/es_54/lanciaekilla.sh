#!/bin/bash

PIDS=`./lanciaeprendipid.sh`
echo $PIDS

for proc in $PIDS; do
	kill -9 $proc;
done;
