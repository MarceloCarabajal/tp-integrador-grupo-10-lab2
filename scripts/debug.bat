@echo off
echo COMPILANDO VETE++ PARA DEBUGGEAR
echo:
set flags=-std=c++14 -Wall -pedantic -pedantic-errors
set includes=-I include/
::set includes=-I include/provisional/
set lib=-L lib/ -lquickmail -lwinmm
set output=bin/vetepp.exe
cd ..
del bin\vetepp.exe
echo g++ -g %flags% %includes% *.cpp src/*.cpp %lib% -o %output%
g++ -g %flags% %includes% *.cpp src/*.cpp %lib% -o %output%
::echo g++ %flags% %includes% *.cpp src/provisional*.cpp %lib% -o %output%
::g++ %flags% %includes% *.cpp src/provisional/*.cpp %lib% -o %output%
echo:
echo Ejecutando gdb vetepp.exe...
cd bin
start gdb vetepp.exe
pause