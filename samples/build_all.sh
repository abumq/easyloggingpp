
#builds all files into bin/
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
find -type f -name '*.cpp' -exec g++ {} -o bin/{}.bin -D $macro \;
