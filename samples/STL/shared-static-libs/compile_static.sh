rm -rf libmyLib.so lib/libmyLib.so lib/mylib.o lib/myLib.a myLib.a myapp logs ## Clean

compiler=icpc ## Intel C++
standard=c++11 ## If this does not work try c++0x (depends on your compiler)
macros="-D_ELPP_THREAD_SAFE -D_ELPP_STACKTRACE_ON_CRASH"  ## Macros for library

cd lib/
$compiler --std=$standard -pipe -fPIC -g -O0 $macros -Iinclude  -c -o mylib.o mylib.cpp
ar rvs myLib.a mylib.o
cp myLib.a ..
cd ..
$compiler -g -std=$standard -o myapp myapp.cpp -Ilib/include myLib.a
