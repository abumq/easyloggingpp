
[ -d "bin" ] || mkdir "bin"
rm -rf bin/*

if [ "$1" = "updated" ];then
    cp ../../easylogging++.h .
fi

find -maxdepth 1 -type f -name '*.cpp' -exec sh compile.sh {} \;

echo "Completed!"
