
# Builds all files into bin/

# USAGE
# sh build_all.sh -> linux build with EasyLogging++ enabled
# sh build_all.sh MAC -> mac specific build
# sh build_all.sh WINDOWS -> window specific build
# sh build_all.sh WINDOWS disable -> window specific build with EasyLogging++ disabled
# sh build_all.sh MAC disable -> mac specific build with EasyLogging++ disabled
# sh build_all.sh disable -> linux build with EasyLogging++ disabled

[ -d "bin" ] || mkdir "bin"
rm -rf bin/*
if [ "$1" = "WINDOWS" ];then
  macro="_WIN32"
else
  if [ "$1" = "MAC" ];then
    macro="__APPLE__"
  else
    macro="__linux"
  fi
fi
if [ "$1" = "disable" ] || [ "$2" = "disable" ]; then
  macro=$macro' -D _DISABLE_LOGS'
fi

## Extra macros
macro="$macro -D _QUALITY_ASSURANCE"
macro="$macro -D _ALWAYS_CLEAN_LOGS"

find -maxdepth 1 -type f -name '*.cpp' -exec g++ {} -o bin/{}.bin -D $macro \;
