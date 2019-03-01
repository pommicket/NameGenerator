#!/bin/bash

VERSION=0-0-0

./build.sh
./build_win.sh

cd bin
zip namegenerator-release-win32-"$VERSION".zip namegenerator_client_32.exe trigrams.txt
zip namegenerator-release-win64-"$VERSION".zip namegenerator_client_64.exe trigrams.txt
zip namegenerator-release-linux-"$VERSION".zip namegenerator_client trigrams.txt
cd ..