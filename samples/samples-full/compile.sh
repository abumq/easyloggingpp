## Helper script for build_all.sh

FILE=$1

if [ "$2" = "WINDOWS" ];then
  macro="_WIN32"
else
  if [ "$2" = "MAC" ];then
    macro="__APPLE__"
  else
    macro="__linux"
  fi
fi

if [ "$2" = "disable" ] || [ "$3" = "disable" ]; then
  macro="$macro -D _DISABLE_LOGS"
fi

## Extra macros
macro="$macro -D _QUALITY_ASSURANCE"
macro="$macro -D _ALWAYS_CLEAN_LOGS"

CXX_STD='-std=c++0x -pthread'

if [ "$FILE" = "" ]; then
  echo "Please provide filename to compile"
  exit
fi

echo "Compiling... [$FILE]"

if [ "$macro" = "" ];then
  g++ $FILE -o $FILE.bin $CXX_STD
else
  g++ $FILE -o bin/$FILE.bin -D $macro $CXX_STD
fi
echo "\tDONE! [./bin/$FILE.bin]"
