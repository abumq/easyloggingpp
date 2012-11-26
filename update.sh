#!/bin/bash

## update.sh v1.5
## Please see 'Update EasyLogging++' section on README.md on
## https://github.com/mkhan3189/EasyLoggingPP/ for more information on this file
## @author mkhan3189
## @since 3.0
## http://tools.icplusplus.com/easylogging/

currFile=$1
targetFile=$2
newVersionFile=$3
echo
echo 'Update EasyLogging++'
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

[ -f "$targetFile" ] || rm $targetFile

## Get comments off new version file
commentsStart=1
commentsEnd=$(grep -n 'Free Software Foundation' $newVersionFile | grep -o '[0-9]*:' | grep -o '[0-9]*')
commentsEnd=$(expr $commentsEnd + 3)
commentsSed="$commentsStart,$commentsEnd"
echo "Updating comments ($commentsStart - $commentsEnd)..."
sed -n $commentsSed'p' $newVersionFile >> $targetFile
## Get logging defines and headers off curr file
headersStart=$(grep -n '#ifndef EASYLOGGINGPP_H' $currFile | grep -o '[0-9]*')
headersEnd=$(grep -n 'EXCEPT CONFIGURATION' $currFile | grep -o '[0-9]*')
headersEnd=$(expr $headersEnd + 3) 
headersSed="$headersStart,$headersEnd"
echo "Updating logging levels ($headersStart - $headersEnd)..."
sed -n $headersSed'p' $currFile >> $targetFile
## Get includes off new version file
includesStart=$(expr $headersEnd + 1)
includesEnd=$(grep -n 'CONFIGURATION FOR LOGGING' $newVersionFile | grep -o '[0-9]*')
includesEnd=$(expr $includesEnd + 5)
includesSed="$includesStart,$includesEnd"
echo "Updating includes ($includesStart - $includesEnd)..."
sed -n $includesSed'p' $currFile >> $targetFile
## Get configurations off currfile
confStart=$(expr $includesEnd + 1)
confEnd=$(grep -n 'END OF CONFIGURATION' $currFile | grep -o '[0-9]*')
confEnd=$(expr $confEnd + 5)
confSed="$confStart,$confEnd"
echo "Updating configuration ($confStart - $confEnd)..."
sed -n $confSed'p' $currFile >> $targetFile
# Get source code off new file
srcStart=$(expr $confEnd + 1)
srcEnd=$(wc -l $newVersionFile | grep -o '[0-9]*')
srcSed="$srcStart,$srcEnd"
echo "Updating source code... ($srcStart - srcEnd)"
sed -n $srcSed'p' $newVersionFile >> $targetFile

echo 'DONE!'
