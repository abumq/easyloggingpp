# Get original file
if [ "$1" = "updated" ];then
  cp ../easylogging++.h .
fi
# Compile
g++ main.cc -lgtest -pthread -o alltests -Wno-unused-result -D_STOP_ON_FIRST_ELPP_ASSERTION -D_ELPP_STRICT_ROLLOUT -D_ELPP_STL_LOGGING
# Run
./alltests
# Clean
rm alltests
rm -rf logs/
