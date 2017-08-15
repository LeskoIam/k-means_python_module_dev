@echo off
REM Clean remnants from last build
del build\ckmeans.pyd
del ckmeans.o
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
gcc -c -I C:\Python27\include ckmeans.c ..\lib\k_means.c ..\lib\utils.c
@echo off
goto :link

REM Compile with debug
:debug
echo on
gcc -c -DDEBUG -I C:\Python27\include ckmeans.c ..\lib\k_means.c ..\lib\utils.c
@echo off

REM Link to pyd
:link
echo on
gcc -shared ckmeans.o k_means.o utils.o -L C:/Python27/libs -lpython27 -o build/ckmeans.pyd
@echo off

REM Test module
cd build
python test_module.py
cd ..
