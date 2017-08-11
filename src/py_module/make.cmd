gcc -c -I C:\Python27\include testmodule.c k_means.c ..\lib\utils.c
gcc -shared testmodule.o k_means.o utils.o -L C:/Python27/libs -lpython27 -o build/testmodule.pyd
