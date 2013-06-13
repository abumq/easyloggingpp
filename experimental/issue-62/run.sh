g++ main.cc -o prog
if [ "$1" = "valgrind" ];then
    valgrind ./prog
else
    ./prog
fi
rm prog
