## !/bin/bash
##
## Updates EasyLogging++ library to latest version
## by fetching it from the web and unzipping.
##
## Required packages:
##   wget
##   unzip
## Revision 1.0
## This script is free of charge

echo "EasyLogging++ Updater"
echo
if [ "$1" = "" ];then
  echo "Please specify existing easylogging++.h location e.g, src/lib/logging/easylogging++.h"
  exit
fi
target=$1
echo "Updating library to $target"
## Remove any previous version of downloaded file
if [ -f "easyloggingpp.zip" ]; then
  echo "Removing existing zip file..."
  rm easyloggingpp.zip
fi
## Get latest version of library
wget http://icplusplus.com/tools/easylogging/easyloggingpp.zip
## Unzip recently downloaded version
unzip easyloggingpp.zip
## Remove zip file
rm easyloggingpp.zip
## Move header to target
mv easylogging++.h $target
