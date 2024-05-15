#! /bin/bash

clang++ -std=c++98 -Wall -pedantic -mconsole main2.cpp -L/./ -lmingw32 -lsdl2main -lsdl2 -o game.exe
