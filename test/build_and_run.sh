
# Builds all tests into bin/ and runs

[ -d "bin" ] || mkdir "bin"

cd bin
echo "Building..."
g++ ../*.cc -std=c++11 -pthread -lgtest -I/usr/local/include/gtest/ -DELPP_FEATURE_ALL -Wall -Wextra -pedantic -pedantic-errors -Werror -Wfatal-errors -Wundef -o easyloggingpp-test
echo "Running..."
./easyloggingpp-test
cd ..
echo "Completed!"
