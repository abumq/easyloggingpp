
# Builds all tests into bin/ and runs

[ -d "bin" ] || mkdir "bin"

cd bin
echo "Building...\n"
g++ ../*.cc -std=c++11 -pthread -lgtest -I/usr/local/include/gtest/ -DELPP_NO_DEFAULT_LOG_FILE -DELPP_FEATURE_ALL -Wall -Wextra -pedantic -pedantic-errors -Werror -Wfatal-errors -Wundef -o easyloggingpp-test && echo "Running...\n" && ./easyloggingpp-test -v
cd ..
echo "Completed!"
