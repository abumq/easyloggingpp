#!/bin/bash

## update.sh v1.1
## Please see 'Updating to Newer Version' section on README.md on https://github.com/mkhan3189/EasyLoggingPP/ for more information on this file
## @author mkhan3189
## @since 2.8

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

if [ "$3" = "" ];then
  usage
  exit
fi

if [ "$currFile" = "$targetFile" ];then
  echo 'Target file has to be different from current file'
  exit
fi

echo "Current File : $currFile"
echo "targetFile : $targetFile"
echo "newVersionFile : $newVersionFile"
## Get comments off new version file
commentsStart=$(grep -n 'easylogging++.h - Core of EasyLogging++' $newVersionFile | grep -o '[0-9]*')
commentsStart=$(expr $commentsStart - 1)
commentsEnd=$(grep -n 'Free Software Foundation' $newVersionFile | grep -o '[0-9]*:' | grep -o '[0-9]*')
commentsEnd=$(expr $commentsEnd + 1)
commentsSed="$commentsStart,$commentsEnd"
sed -n $commentsSed'p' $newVersionFile > $targetFile
## Get logging defines and headers off curr file
headersStart=$(grep -n '#ifndef EASYLOGGINGPP_H' $currFile | grep -o '[0-9]*')
headersEnd=$(grep -n '#if _LOGGING_ENABLED' $currFile | grep -o '[0-9]*')
headersEnd=$(expr $headersEnd - 2)
headersSed="$headersStart,$headersEnd"
sed -n $headersSed'p' $currFile >> $targetFile
## Get includes off new version file
includesStart=$(grep -n '#if _LOGGING_ENABLED' $newVersionFile | grep -o '[0-9]*')
includesEnd=$(grep -n 'Configuration for logging' $newVersionFile | grep -o '[0-9]*')
includesEnd=$(expr $includesEnd - 2)
includesSed="$includesStart,$includesEnd"
sed -n $includesSed'p' $currFile >> $targetFile
## Get configurations off currfile
confStart=$(grep -n 'Configuration for logging' $currFile | grep -o '[0-9]*')
confStart=$(expr $confStart - 1)
confEnd=$(grep -n 'END OF CONFIGURATION FOR LOGGING' $currFile | grep -o '[0-9]*')
confEnd=$(expr $confEnd + 1)
confSed="$confStart,$confEnd"
sed -n $confSed'p' $currFile >> $targetFile
# Get source code off new file
srcStart=$(grep -n 'END OF CONFIGURATION FOR LOGGING' $newVersionFile | grep -o '[0-9]*')
srcStart=$(expr $srcStart + 2)
srcEnd=$(wc -l $newVersionFile | grep -o '[0-9]*')
srcSed="$srcStart,$srcEnd"
sed -n $srcSed'p' $newVersionFile >> $targetFile

echo 'DONE!'
