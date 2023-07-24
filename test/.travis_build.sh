echo "Use cmake"
exit 1

echo "Compiling unit tests..."
clang++ *.cc -lgtest -std=c++14 -lpthread -o unit_test -D_ELPP_DEFAULT_LOG_FILE='"logs/el.gtest.log"' -DELPP_LOGGING_FLAGS_FROM_ARG -DELPP_FEATURE_ALL -Wall -Wextra -pedantic -pedantic-errors -DELPP_SYSLOG -Werror -Wfatal-errors -Wno-dangling-gsl -Wundef -v
echo "Running unit tests..."
./unit_test -v
result=$?
rm -r unit_test logs
echo "Unit tests completed : $result"
exit $result
