NUM=$#

while (( NUM >= 1 ));  do
	echo -n ${!NUM}" ";
	(( NUM = $NUM - 1 ))
done;

echo $'\n'
