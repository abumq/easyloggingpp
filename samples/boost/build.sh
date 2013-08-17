if [ "$3" = "" ];then
    echo "Usage: $0 [boost-src-path] [compiler] [file]"
    exit 1
fi

compiler=$2

[ -d "bin" ] || mkdir "bin"
rm -rf bin/*

cp ../../src/easylogging++.h .


$compiler -I$1 $3 -o bin/$3.bin -std=c++11

rm easylogging++.h
