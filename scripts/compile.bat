@echo off
echo COMPILANDO VETE++
echo:
set flags=-std=c++14 -Wall -pedantic -pedantic-errors
set includes=-I include/
set lib=-L lib/ -lquickmail 
set output=bin/vetepp.exe
cd ..
echo g++ %flags% %includes% *.cpp src/*.cpp %lib% -o %output%
g++ %flags% %includes% *.cpp src/*.cpp %lib% -o %output%
echo:
echo Ejecutando vetepp.exe...
start bin/vetepp.exe
pause