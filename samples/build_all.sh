
#builds all files into bin/
[ -d "bin" ] || mkdir "bin"
rm -rf bin/*
find -type f -name '*.cpp' -exec g++ {} -o bin/{}.bin \;
