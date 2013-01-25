
# Build and run tests for EasyLogging++

macro="$macro -D _QUALITY_ASSURANCE"
macro="$macro -D _ALWAYS_CLEAN_LOGS"

g++ tests.cpp -o tests.bin $macro
./tests.bin
