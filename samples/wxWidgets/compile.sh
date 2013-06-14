## Helper script for build_all.sh

FILE=$1
if [ "$FILE" = "" ]; then
  echo "Please provide filename to compile"
  exit
fi
## Extra macros
macro="-D_QUALITY_ASSURANCE"
macro="$macro -D_ELPP_STL_LOGGING"
macro="$macro -D_ELPP_WXWIDGETS_LOGGING"

CXX_STD='-std=c++0x -pthread'

echo "Compiling... [$FILE]"
g++ $FILE `wx-config --libs` `wx-config --cxxflags` -o bin/$FILE.bin $macro $CXX_STD
echo "\tDONE! [./bin/$FILE.bin]"
