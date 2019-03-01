#!/bin/bash
mkdir -p bin
cp trigrams.txt bin/
# cmake not working with mingw for some reason. I'm just compiling it manually 

i686-w64-mingw32-gcc -o bin/namegenerator_client_32.exe src/namegenerator/namegenerator.c src/main.c
x86_64-w64-mingw32-gcc -o bin/namegenerator_client_64.exe src/namegenerator/namegenerator.c src/main.c


