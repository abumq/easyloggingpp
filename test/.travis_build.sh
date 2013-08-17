clang++ main.cc -lgtest -std=c++11 -lpthread -o unit_test
./unit_test -v
result=$?
rm -r unit_test logs
echo "Unit tests completed : $result"
exit $result
