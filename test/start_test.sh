# Start tests for EasyLogging++
# Author mkhan3189

echo 'Copying...'
cp ../easylogging++.h .

echo 'Running tests...'

bash run_unit_tests.sh

echo 'Cleaning...'
rm easylogging++.h
rm -rf logs
