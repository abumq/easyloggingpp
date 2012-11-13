CURR_VERSION=$(grep 'EasyLogging++ v' easylogging++.h | grep -o '[0-9].[0-9]')
NEW_VERSION=$1
DO_NOT_CONFIRM=$2
if [ "$NEW_VERSION" == "" ];
then
  echo 'Current Version  ' $CURR_VERSION
  echo '** No version provided **'
  exit
fi

echo 'Current Version  ' $CURR_VERSION
echo 'New Version      ' $NEW_VERSION

if [ "$DO_NOT_CONFIRM" == "y" ];
then
  confirm="y"
else
  echo 'Are you sure? (y/n)' 
  read confirm
fi

if [ "$confirm" = "y" ];
then
  sed -i "s/EasyLogging++ v[0-9]*.[0-9]*/EasyLogging++ v$NEW_VERSION/g" easylogging++.h
  sed -i "s/\$currentVersion = \"v[0-9]*.[0-9]*/\$currentVersion = \"v$NEW_VERSION/g" index.php
  if [ -f "easyloggingpp_$NEW_VERSION.zip" ];
  then
    rm releases/easyloggingpp_$NEW_VERSION.zip
  fi
  zip releases/easyloggingpp_$NEW_VERSION.zip easylogging++.h
fi
