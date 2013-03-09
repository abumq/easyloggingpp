#!/bin/sh

function test {
  echo
  echo "TESTING: g++ utils/* unit_tests.cpp -o tests.bin $1 -Wno-write-strings"
  echo
  g++ utils/* unit_tests.cpp -o tests.bin $1 -Wno-write-strings
  user=`whoami`
  host=`hostname`
  TEST_RESULT=`./tests.bin $user $host -v`
  FAILED=`echo "$TEST_RESULT" | grep -o 'TEST FAILED' | wc -l`
  if [ "$FAILED" -ne 0 ];then
    echo "$TEST_RESULT"
    exit
  else
    echo "TEST PASSED"
  fi
  rm tests.bin
}

commonMacros="-D_ALWAYS_CLEAN_LOGS -D_SUPPORT_LEGACY_LOG_NAMES"
macro="-D_QUALITY_ASSURANCE $commonMacros"
test "$macro"

macro="-D_DISABLE_LOGS $commonMacros"
test "$macro"

echo
echo 'ALL TESTS WERE PASSED'
