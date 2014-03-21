rm -rf libmyLib.so lib/libmyLib.so lib/mylib.o lib/myLib.a myLib.a myapp logs ## Clean

compiler=g++
standard=c++11 ## If this does not work try c++0x (depends on your compiler)
macros="-D_ELPP_THREAD_SAFE -D_ELPP_STACKTRACE_ON_CRASH"  ## Macros for library

cd lib/
$compiler --std=$standard -pipe -fPIC -g -O0  $macros  -Iinclude  -c mylib.cpp -o mylib.o 
$compiler -fPIC -g  -shared -o libmyLib.so mylib.o
cp libmyLib.so ..
cd ..
$compiler -g -std=$standard $macros -fPIC -pipe  -Wl,-rpath=lib -L lib myapp.cpp -Ilib/include -lmyLib  -o myapp
