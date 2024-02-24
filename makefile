CC = g++
EXE = output/app

FILES = src/lexer.cpp src/main.cpp src/SMachine.cpp

all: compile

compile:
	$(CC) $(FILES) -o $(EXE)
