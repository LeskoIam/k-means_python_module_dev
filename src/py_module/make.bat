@echo off
REM Clean remnants from last build
del build\testmodule.pyd
del testmodule.o
del k_means.o
del utils.o

if "%~1"=="-D" (
    echo[
    echo Building with -DDEBUG flag
    echo Please use module with debug flag enabled with small number of points only!
    echo Otherwise you will get a flood of text.
    echo[
    goto :debug
)


REM Compile without debug
echo on
gcc -c -I C:\Python27\include testmodule.c ..\lib\k_means.c ..\lib\utils.c
@echo off
goto :link

:debug
REM Compile with debug
echo on
gcc -c -DDEBUG -DDEBUG -I C:\Python27\include testmodule.c ..\lib\k_means.c ..\lib\utils.c
@echo off

:link
REM Link
echo on
gcc -shared testmodule.o k_means.o utils.o -L C:/Python27/libs -lpython27 -o build/testmodule.pyd
@echo off

REM Test module
cd build
python test_module.py
cd ..
