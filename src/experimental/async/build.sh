compiler=icpc
echo "$compiler prog.cpp -std=c++11 -lpthread -o prog && ./prog"
$compiler prog.cpp -std=c++11 -lpthread -o prog && ./prog
