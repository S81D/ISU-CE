#!/bin/bash

b=$1

for line in `cat TimestampCT5.list`
do
	sh Gain.sh  $line $b 
done

