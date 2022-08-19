#!/bin/bash
FOLDER=$1


#expect -c 'spawn -noecho root -l testA.C
#send "run("
#send "\"/dsk/1/tmp/coldelec/feasic/quadFeAsic/20210927T103232/gain_enc_sequence-g2s2b0-0000/gain_enc_sequence-g2s2b0-0000-20210927T103324-parseBinaryFile.root\");\r"
#send ".q;\r"
#interact'


#expect -c 'spawn -noecho root -l Pulses_All.C
expect -c 'spawn -noecho root -l Linearity.C
send "run("
send "\"/dsk/1/tmp/coldelec/feasic/quadFeAsic/"
send "'$FOLDER'"
send "\""
send ");\r"
send ".q;\r"
interact'

#mv example1.dat "$file".dat


