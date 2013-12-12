rm -rf libmyLib.so lib/libmyLib.so lib/mylib.o lib/myLib.a myLib.a myapp logs ## Clean

compiler=icpc ## Intel C++

cd lib/
$compiler --std=c++11 -pipe -fPIC -g -O0  -D_ELPP_THREAD_SAFE -D_ELPP_STACKTRACE_ON_CRASH  -Iinclude  -c -o mylib.o mylib.cpp
ar rvs myLib.a mylib.o
cp myLib.a ..
cd ..
$compiler -g -std=c++11 -o myapp myapp.cpp -Ilib/include myLib.a
