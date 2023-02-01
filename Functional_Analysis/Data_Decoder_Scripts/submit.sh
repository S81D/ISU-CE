#!/bin/bash

b=$1

for line in `cat Timestamps.list`
do
	sh AllChannels.sh  $line $b 
done

