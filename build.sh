#!/bin/bash
mkdir -p bin
cp trigrams.txt bin/
cd bin
cmake ../src && make
cd ..
