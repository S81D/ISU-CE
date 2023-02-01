#!/bin/bash

#paste -d '' TimestampRT0list.list timePaths.list > Next2.list

paste -d '' Time_CT20.list time__CT20.list > Next4.list



for VARIABLE in $(cat Next4.list) 

do
	sh PulseHeight.sh $VARIABLE
	#echo "$file"
	
	file=$VARIABLE
	n=${file%/*}
	n=${n%/gain*}
	echo $n
	
	#mv example1.dat PulseHeightCT5/$n.dat
	#mv example1.dat IC_CT20/$n.dat
	mv example1.dat LinearityCT20/$n.dat


	#rm example1.dat
done

