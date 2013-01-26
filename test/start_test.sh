# Build and run tests for EasyLogging++
# Author mkhan3189

echo 'Compiling...'

macro="$macro -D _QUALITY_ASSURANCE"
macro="$macro -D _ALWAYS_CLEAN_LOGS"

if [ -f "tests.bin" ];then
  rm tests.bin
fi

g++ basic_tests.cpp main.cpp -o tests.bin $macro -Wno-write-strings

echo 'Running tests...'

user=$(whoami)
host=$(hostname)
./tests.bin $user $host 
