compiler=icpc
echo "$compiler prog.cpp -D_ELPP_EXPERIMENTAL_ASYNC -std=c++11 -lpthread -o prog && ./prog"
$compiler prog.cpp -D_ELPP_EXPERIMENTAL_ASYNC -std=c++11 -lpthread -o prog && ./prog
