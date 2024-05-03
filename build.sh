#! /bin/bash

clang++ -W -std=c++98 -mconsole main2.cpp -L/./ -lmingw32 -lsdl2main -lsdl2 -o game.exe
