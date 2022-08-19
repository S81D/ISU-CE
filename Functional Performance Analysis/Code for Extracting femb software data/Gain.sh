#!/bin/bash
FOLDER=$1
b=$2
file=$3
gain=$4

temp=$5



#grep "fail"  /dsk/1/tmp/coldelec/feasic/quadFeAsic/$FOLDER/gain_enc_sequence-g2s2$b-0000/*.list
#grep "fail" 1.list
tail -64 /dsk/1/tmp/coldelec/feasic/quadFeAsic/$FOLDER/gain_enc_sequence-g2s2$b-0000/*.list>1.list 

grep "fail" 1.list>2.list 

#cut -c 34- | cut -d '"' -f1<1.list



#cut -c9-29 2.list
# cut from the period; if -f 2  -->   got to the second period and cut to the left
# Column assignments then go from the far left period towards the period specified
cut -d "," -f 2 2.list | cut -c 5-11 >temp1.txt    # RMS
cut -d "," -f 3 2.list | cut -c 6-12 >temp2.txt    # Mean
cut -d "," -f 1 2.list | cut -c 3-5 >temp3.txt     # Ch Number
cut -d "," -f 6 2.list | cut -c 6-7 >temp4.txt     # P/F
cut -d "," -f 4 2.list | cut -c 6-10 >temp5.txt     # Gain
cut -d "," -f 5 2.list | cut -c 5-9 >temp6.txt     # ENC

pr -m -t temp1.txt temp2.txt temp3.txt temp4.txt temp5.txt temp6.txt  >NaNCT/$FOLDER.dat
rm temp1.txt temp2.txt temp3.txt 1.list 2.list temp4.txt temp5.txt temp6.txt


#cut -c23-30 2.list
#grep -o '.$' 2.list

#pr -m -t ch.txt f.txt >temp.txt

#sed 's/,//g'  temp.txt

#sed 's/[^0-9]*//g' test.txt
