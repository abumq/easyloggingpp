
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

## Get latest copy
if [ "$1" = "use-old" ];then
    echo 'Using existing header...'
else
    cp ../../easylogging++.h .
fi

find -maxdepth 1 -type f -name '*.cpp' -exec sh compile.sh {} $1 $2 \;
echo "Completed!"
