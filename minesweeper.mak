# 27/4/2017 - 
# Uso: make -f minesweeper.mak

OBJ=./obj
BIN=./bin
LIB=./lib
SRC=./src
INC=./include

all: $(BIN)/Minesweeper 

$(BIN)/Minesweeper: $(SRC)/Main.cpp $(OBJ)/Tablero.o
	g++ $(SRC)/Main.cpp $(OBJ)/Tablero.o -I$(INC) -std=c++11 -lSDL2 -lSDL2_image -o $@

$(OBJ)/Tablero.o: $(SRC)/Tablero.cpp $(INC)/Tablero.h
	g++ -c $(SRC)/Tablero.cpp -I$(INC) -std=c++11 -lSDL2 -lSDL2_image -o $@

clean:
	@printf "Borrando modulos objeto...\n"
	rm $(OBJ)/*.o

mrproper: clean
	@printf "Borrando ejecutables...\n"
	rm $(BIN)/*
