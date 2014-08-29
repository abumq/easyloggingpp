compiler=g++
echo "$compiler prog.cpp -D_ELPP_EXPERIMENTAL_ASYNC_LOGGING -std=c++11 -lpthread -o prog && ./prog"
echo '' > logs/myeasylog.log && $compiler prog.cpp -D_ELPP_EXPERIMENTAL_ASYNC_LOGGING -std=c++11 -lpthread -o prog && ./prog
