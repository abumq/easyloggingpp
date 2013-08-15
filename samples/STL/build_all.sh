
# Builds all files into bin/

[ -d "bin" ] || mkdir "bin"
rm -rf bin/*

cp ../../src/easylogging++.h .

find -maxdepth 1 -type f -name '*.cpp' -exec sh compile.sh {} $1 \;
echo "Completed!"
rm easylogging++.h

files=$(ls -l bin/)
if [ "$files" = "total 0" ];then
  exit 1
else
  exit 0
fi
