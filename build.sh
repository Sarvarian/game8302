#! /bin/bash

clang++ -W -std=c++98 -mconsole pch.cpp main.cpp ab/actor.cpp -L/./ -lmingw32 -lsdl2main -lsdl2 -o game.exe
