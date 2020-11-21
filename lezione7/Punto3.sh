RIGA="1 * 2"

while true; do
	STAMPA="${RIGA%% *}"
	echo "$STAMPA"
	RIGA="${RIGA#$STAMPA }"
	if [[ "$RIGA" == "$STAMPA" ]]; then
		break;
	fi;
done;
