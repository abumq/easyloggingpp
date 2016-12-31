echo "Compiling unit tests..."
clang++ *.cc -lgtest -I /usr/lib/ -std=c++11 -lpthread -o unit_test -D_ELPP_DEFAULT_LOG_FILE='"logs/el.gtest.log"' -DELPP_FEATURE_ALL -Wall -Wextra -pedantic -pedantic-errors -Werror -Wfatal-errors -Wundef
echo "Running unit tests..."
./unit_test -v
result=$?
rm -r unit_test logs
echo "Unit tests completed : $result"
exit $result
