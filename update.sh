#!/bin/bash

## Please see 'Updating to Newer Version' section on README.md on https://github.com/mkhan3189/EasyLoggingPP/ for more information on this file
## @author mkhan3189

currFile=$1
targetFile=$2
newVersionFile=$3
echo
echo 'UPDATE EasyLogging++'
usage(){
  echo
  echo 'USAGE'
  echo '====='
  echo $0 ' [currFile] [targetFile] [newVersionFile]'
  echo 'currFile : easylogging++.h file that you wish to retain configuration from.'
  echo 'targetFile : easylogging++.h file with updated code and same old configuration settings.'
  echo 'newVersionFile : easylogging++.h file whose source code you would like to use.'
  echo
}

verify(){
if [ "$1" -eq "-h" ];
then
  usage
  exit
fi

if [ "$3" -eq "" ];
then
  usage
  exit
fi

if [ "$currFile" -eq "$targetFile" ];
then
  echo 'Target file has to be different from current file'
fi
}

verify
echo "Current File : $currFile"
echo "targetFile : $targetFile"
echo "newVersionFile : $newVersionFile"
## Get comments off new version file
start1=$(grep -n 'easylogging++.h - Core of EasyLogging++' $newVersionFile | grep -o '[0-9]*')
start1=$(expr $start1 - 1)
end1=$(grep -n 'Free Software Foundation' $newVersionFile | grep -o '[0-9]*:' | grep -o '[0-9]*')
end1=$(expr $end1 + 1)
sed1="$start1,$end1"
comments=$(sed -n $sed1'p' $newVersionFile > $targetFile)
## Get configurations off old file
start2=$(grep -n '#ifndef EASYLOGGINGPP_H' $currFile | grep -o '[0-9]*')
end2=$(grep -n 'END OF CONFIGURATION FOR LOGGING' $currFile | grep -o '[0-9]*')
end2=$(expr $end2 + 1)
sed2="$start2,$end2"
conf=$(sed -n $sed2'p' $currFile >> $targetFile)
# Get source code off new file
start3=$(grep -n 'END OF CONFIGURATION FOR LOGGING' $newVersionFile | grep -o '[0-9]*')
start3=$(expr $start3 + 2)
end3=$(wc -l $newVersionFile | grep -o '[0-9]*')
sed3="$start3,$end3"
src=$(sed -n $sed3'p' $newVersionFile >> $targetFile)

echo 'DONE!'
