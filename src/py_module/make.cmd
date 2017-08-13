REM Clean remnants from last build
del build\testmodule.pyd
del testmodule.o
del k_means.o
del utils.o

REM Compile
gcc -c -I C:\Python27\include testmodule.c ..\lib\k_means.c ..\lib\utils.c
REM Link
gcc -shared testmodule.o k_means.o utils.o -L C:/Python27/libs -lpython27 -o build/testmodule.pyd

REM TEST
cd build
python test_module.py
cd ..
