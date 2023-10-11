@echo off
@echo Compilando main_tests.cpp
set flags=-std=c++14 -Wall -pedantic -pedantic-errors
cd ../tests/
g++  %flags% -I ../include/ -I ../src/ *.cpp ../src/*.cpp -o main_tests && start main_tests.exe
pause