echo "Compiling unit tests..."
clang++ main.cc -lgtest -std=c++11 -lpthread -o unit_test
echo "Running unit tests..."
./unit_test -v
result=$?
rm -r unit_test logs
echo "Unit tests completed : $result"
exit $result
