if [ "$1" = "copy" ];then
  cp ../easylogging++.h .
fi
g++ main.cc -o main && ./main -v && rm main
