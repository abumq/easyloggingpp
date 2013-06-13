g++ main.cc -o prog
if [ "$1" = "valgrind" ];then
    valgrind --leak-check=full ./prog
else
    ./prog
fi
rm prog
