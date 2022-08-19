#!/bin/bash

#for line in 'cat Next.list'

#do
#	sh testtest.sh $line
#done


#cat TimestampRT0list.list | while read line

cat Time_CT20.list | while read line
do
	sh testtest.sh $line
done
