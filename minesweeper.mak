# Uso: make -f minesweeper.mak

OBJ=./obj
BIN=./bin
LIB=./lib
SRC=./src
INC=./include


all: $(BIN)/Minesweeper $(OBJ)/Tablero.o

$(BIN)/Minesweeper: $(SRC)/Main.cpp
	g++ -o $@ $^ -lSDL2 -lSDL2_image

$(OBJ)/Tablero.o: $(SRC)/Tablero.cpp
	g++ -c -o $@ $^ -std=c++11

clean:
	@printf "Borrando modulos objeto...\n"
	rm $(OBJ)/*.o

mrproper: clean
	@printf "Borrando ejecutables...\n"
	rm $(BIN)/*
