for name in `ls`; do
	echo $name;
	VAR=`ls -ld $name`
	if [[ -z $VAR ]]; then
		echo "ls produce errore";
	fi;
done;
