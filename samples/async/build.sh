compiler=$1
macros=""
if [ "$compiler" = "icpc" ];then
    macros="$macros -DELPP_NO_SLEEP_FOR"
fi
echo "$compiler prog.cpp -DELPP_EXPERIMENTAL_ASYNC $macros -std=c++11 -lpthread -o prog"
$compiler prog.cpp -DELPP_EXPERIMENTAL_ASYNC $macros -std=c++11 -lpthread -o prog
