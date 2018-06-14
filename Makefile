CC=gcc
SRC=src
OUT=./NameGenerator

default: all

all: $(SRC)/*.c $(SRC)/*.h
	$(CC) -o $(OUT) $(SRC)/*.c

run: all
	$(OUT)
