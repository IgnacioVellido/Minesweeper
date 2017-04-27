# 27/4/2017 - 
# Uso: make -f minesweeper.mak

OBJ=./obj
BIN=./bin
LIB=./lib
SRC=./src
INC=./include


all: $(BIN)/Minesweeper $(OBJ)/Tablero.o $(OBJ)/Interfaz.o $(OBJ)/Main.o

$(BIN)/Minesweeper: $(SRC)/Main.cpp $(OBJ)/Tablero.o $(OBJ)/Interfaz.o
	g++ -o $@ $^ -I$(INC) -std=c++11

#$(OBJ)/Main.o: $(SRC)/Main.cpp $(LIB)/libInterfaz.a
#	g++ -c-o $@ $(SRC)/Main.cpp -L/$(LIB)

$(OBJ)/Tablero.o: $(SRC)/Tablero.cpp $(INC)/Tablero.h $(OBJ)/Interfaz.o
	g++ -c -o $@ $(SRC)/Tablero.cpp $(OBJ)/Interfaz.o -I$(INC) -std=c++11 -lSDL2 -lSDL2_image

#$(LIB)/libInterfaz.a: $(OBJ)/Interfaz.o
#	ar -rvs $@ $^

$(OBJ)/Interfaz.o: $(SRC)/Interfaz.cpp $(INC)/Interfaz.h
	g++ -c -o $@ $(SRC)/Interfaz.cpp -I$(INC) -lSDL2 -lSDL2_image

clean:
	@printf "Borrando modulos objeto...\n"
	rm $(OBJ)/*.o

mrproper: clean
	@printf "Borrando ejecutables...\n"
	rm $(BIN)/*
