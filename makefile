CC = g++
EXE = comp/output/compiler

FILES = comp/src/lexer.cpp comp/src/main.cpp com/src/SMachine.cpp

comp:
	$(CC) $(FILES) -o $(EXE)
	clear

asm:
	
