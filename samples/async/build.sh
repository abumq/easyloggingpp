compiler=icpc
echo "$compiler prog.cpp -DELPP_EXPERIMENTAL_ASYNC -std=c++11 -lpthread -o prog && ./prog"
$compiler prog.cpp -DELPP_EXPERIMENTAL_ASYNC -std=c++11 -lpthread -o prog && ./prog
