
#builds all files into bin/
find -type f -name '*.cpp' -exec g++ {} -o bin/{}.bin \;
