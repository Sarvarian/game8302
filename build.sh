#! /bin/bash

clang++ -W -mconsole main.cpp -L/./ -lmingw32 -lsdl2main -lsdl2 -o game.exe
