#!/bin/bash

# Bash script that helps with releasing new versions of EasyLogging++
# Revision: 1.1
# @author mkhan3189

[ -d "releases" ] || mkdir releases

CURR_VERSION=$(grep 'EasyLogging++ v' easylogging++.h | grep -o '[0-9].[0-9][0-9]*')
CURR_RELEASE_DATE=$(grep -o '[0-9][0-9]-[0-9][0-9]-201[2-9] [0-9][0-9][0-9][0-9]hrs' easylogging++.h)
NEW_RELEASE_DATE=$(date +"%d-%m-%Y %H%Mhrs")
NEW_VERSION=$1
DO_NOT_CONFIRM=$2
if [ "$NEW_VERSION" = "" ]; then
  echo 'Current Version  ' $CURR_VERSION
  echo '** No version provided **'
  exit
fi

echo 'Current Version  ' $CURR_VERSION ' (' $CURR_RELEASE_DATE ')'
echo 'New Version      ' $NEW_VERSION  ' (' $NEW_RELEASE_DATE ')'
if [ "$DO_NOT_CONFIRM" = "y" ]; then
  confirm="y"
else
  echo 'Are you sure you wish to release new version? (y/n)' 
  read confirm
fi

if [ "$confirm" = "y" ]; then
  sed -i "s/EasyLogging++ v$CURR_VERSION*/EasyLogging++ v$NEW_VERSION/g" easylogging++.h
  sed -i "s/version(void) { return std::string(\"$CURR_VERSION\"); }/version(void) { return std\:\:string(\"$NEW_VERSION\"); }/g" easylogging++.h
  sed -i "s/releaseDate(void) { return std::string(\"$CURR_RELEASE_DATE\"); }/releaseDate(void) { return std\:\:string(\"$NEW_RELEASE_DATE\"); }/g" easylogging++.h
  sed -i "s/\$currentVersion = \"v $CURR_VERSION\"*/\$currentVersion = \"v $NEW_VERSION\"/g" homepage/index.php
  sed -i "s/\$releaseDate = \"$CURR_RELEASE_DATE\"*/\$releaseDate = \"$NEW_RELEASE_DATE\"/g" homepage/index.php
  sed -i "s/$CURR_RELEASE_DATE/$NEW_RELEASE_DATE/g" homepage/index.php 
  sed -i "s/v$CURR_VERSION/v$NEW_VERSION/g" README.md
  sed -i "s/easyloggingpp_$CURR_VERSION.zip/easyloggingpp_$NEW_VERSION.zip/g" README.md
  if [ -f "easyloggingpp_v$NEW_VERSION.zip" ]; then
    rm releases/easyloggingpp_v$NEW_VERSION.zip
  fi
  if [ -f "easyloggingpp.zip" ]; then
    rm easyloggingpp.zip
  fi
  zip releases/easyloggingpp_v$NEW_VERSION.zip easylogging++.h
  zip easyloggingpp.zip easylogging++.h
  sh copy-across.sh
fi
