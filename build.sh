#! /bin/bash

clang++ -W -std=c++98 -mconsole main.cpp -L/./ -lmingw32 -lsdl2main -lsdl2 -o game.exe
