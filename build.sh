#! /bin/bash

compilation_files=$(xargs < compilation_files.txt)

clang++ -W -mconsole $compilation_files -L/./ -lmingw32 -lsdl2main -lsdl2 -o game.exe
