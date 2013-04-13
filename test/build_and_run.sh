# Get original file
cp ../easylogging++.h .
# Compile
g++ main.cc -lgtest -pthread -o alltests -Wno-unused-result -D_STOP_ON_FIRST_ELPP_ASSERTION -D_ALWAYS_CLEAN_LOGS
# Run
./alltests
# Clean
rm alltests
rm -rf logs/
rm easylogging++.h
