clang++ main.cc -lgtest -std=c++11 -lpthread -o unit_test
./unit_test -v
rm -r logs unit_test
