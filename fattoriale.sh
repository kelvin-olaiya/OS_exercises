#!/bin/bash
res=1
for ((FACT_START=1; $FACT_START<=$1; FACT_START=$FACT_START+1)); do
	(( res = res * $FACT_START ));
done;
echo $res
