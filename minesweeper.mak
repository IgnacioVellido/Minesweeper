# Uso: make -f minesweeper.mak

OBJ=./obj
BIN=./bin
LIB=./lib
SRC=./src
INC=./include


all: $(BIN)/Minesweeper

$(BIN)/Minesweeper: ./src/Main.cpp
	g++ -o $@ $^ -lSDL2

clean:
	@printf "Borrando modulos objeto...\n"
	rm $(OBJ)/*.o

mrproper: clean
	@printf "Borrando ejecutables...\n"
	rm $(BIN)/*
