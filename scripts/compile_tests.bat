@echo off
@echo Compilando main_tests.cpp
set flags=-std=c++14 -Wall -pedantic -pedantic-errors
set lib=-L ../lib/ -lquickmail -lwinmm
cd ../tests/
g++  %flags% -I ../include/ -I ../src/ main_tests.cpp ../src/*.cpp %lib% -o main_tests && start main_tests.exe
pause