#!/bin/bash

## update.sh v2.0
## Please see 'Update EasyLogging++' section on README.md on
## https://github.com/mkhan3189/EasyLoggingPP/ for more information on this file
## @author mkhan3189
## @since 3.0
## http://tools.icplusplus.com/easylogging/

currentFile=$1
targetFile=$2
newVersionFile=$3
echo
echo ' *** UPDATE EasyLogging++ *** '
echo

usage(){
  echo
  echo 'USAGE'
  echo '====='
  echo $0 ' [currentFile] [targetFile] [newVersionFile]'
  echo 'currentFile : easylogging++.h file that you wish to retain configuration from.'
  echo 'targetFile : easylogging++.h file with updated code and same old configuration settings.'
  echo 'newVersionFile : easylogging++.h file whose source code you would like to use.'
  echo
}

startnow(){
  echo 'Starting update...'
}

initialize(){
  if [ "$newVersionFile" = "" ];then
    usage
    exit
  fi
  if [ "$currentFile" = "$targetFile" ];then
    echo 'Target file has to be different from current file'
    exit
  fi
  echo "Current File   :   $currentFile"
  echo "Target File    :   $targetFile"
  echo "Updating From  :   $newVersionFile"
  echo
  [ ! -f "$targetFile" ] || rm $targetFile
  startnow
}

initialize
