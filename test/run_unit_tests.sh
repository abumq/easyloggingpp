#!/bin/sh

function test {
  echo
  echo "TESTING: g++ utils/* unit_tests.cpp -o tests.bin $1 -Wno-write-strings"
  echo
  g++ utils/* unit_tests.cpp -o tests.bin $1 -Wno-write-strings
  user=`whoami`
  host=`hostname`
  active_levels=$2
  TEST_RESULT=`./tests.bin $user $host $active_levels`
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
test "$macro" 8 ## debug, error, warning, verbose, fatal, qa, info, performance

macro="-D_QUALITY_ASSURANCE -D_DISABLE_PERFORMANCE_LOGS $commonMacros"
test "$macro" 7 ## debug, error, warning, verbose, fatal, qa, info


macro="-D_QUALITY_ASSURANCE -D_DISABLE_PERFORMANCE_LOGS $commonMacros"
test "$macro" 7 ## debug, error, warning, verbose, fatal, qa, info

macro="-D_DISABLE_PERFORMANCE_LOGS -D_DISABLE_INFO_LOGS $commonMacros"
test "$macro" 5 ## debug, error, warning, verbose, fatal

macro="-D_DISABLE_LOGS $commonMacros"
test "$macro" 0

echo
echo 'ALL TESTS WERE PASSED'
