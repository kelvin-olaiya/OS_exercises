#!/bin/bash
NUM=0
(GRUPPO=${BASHPID}; tail -n 10000 -f 7.txt --pid=$GRUPPO | while read C; do (( NUM = $NUM + 1 ));
		if [[ $C == k ]]; then
			echo $NUM
			kill -s SIGTERM $GRUPPO
		fi;
	done;
)
