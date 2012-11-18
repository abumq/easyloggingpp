#!/bin/bash

# Bash script that helps with releasing new versions of EasyLogging++
# @author mkhan3189

[ -d "releases" ] || mkdir releases

CURR_VERSION=$(grep 'EasyLogging++ v' easylogging++.h | grep -o '[0-9].[0-9][0-9]*')
NEW_VERSION=$1
DO_NOT_CONFIRM=$2
if [ "$NEW_VERSION" = "" ]; then
  echo 'Current Version  ' $CURR_VERSION
  echo '** No version provided **'
  exit
fi

echo 'Current Version  ' $CURR_VERSION
echo 'New Version      ' $NEW_VERSION

if [ "$DO_NOT_CONFIRM" = "y" ]; then
  confirm="y"
else
  echo 'Are you sure you wish to release new version? (y/n)' 
  read confirm
fi

if [ "$confirm" = "y" ]; then
  sed -i "s/EasyLogging++ v$CURR_VERSION*/EasyLogging++ v$NEW_VERSION/g" easylogging++.h
  sed -i "s/\$currentVersion = \"v$CURR_VERSION\"*/\$currentVersion = \"v$NEW_VERSION\"/g" index.php
  if [ -f "easyloggingpp_v$NEW_VERSION.zip" ]; then
    rm releases/easyloggingpp_v$NEW_VERSION.zip
  fi
  if [ -f "easyloggingpp.zip" ]; then
    rm easyloggingpp.zip
  fi
  zip releases/easyloggingpp_v$NEW_VERSION.zip easylogging++.h update.sh
  zip easyloggingpp.zip easylogging++.h update.sh
fi
