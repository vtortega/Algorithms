CC = g++
CFLAGS = -Wall -Wextra -pedantic -g -std=c++11
LFLAGS = -lm
SRC = src
OBJ = obj
INC = include
BIN = bin
EXE = $(BIN)/program

OBJS = $(OBJ)/main.o $(OBJ)/node.o $(OBJ)/utility.o $(OBJ)/compressUtility.o $(OBJ)/decompressUtility.o $(OBJ)/myVector.o $(OBJ)/myMap.o $(OBJ)/myPair.o

$(EXE): $(OBJS)
	$(CC) $(OBJS) -o $(EXE) $(LFLAGS)

$(OBJ)/main.o: $(SRC)/main.cpp $(INC)/node.hpp $(INC)/utility.hpp $(INC)/compressUtility.hpp $(INC)/decompressUtility.hpp $(INC)/myVector.hpp $(INC)/myMap.hpp $(INC)/myPair.hpp
	$(CC) -c $(CFLAGS) -I$(INC) $< -o $@

$(OBJ)/node.o: $(SRC)/node.cpp $(INC)/node.hpp
	$(CC) -c $(CFLAGS) -I$(INC) $< -o $@

$(OBJ)/utility.o: $(SRC)/utility.cpp $(INC)/utility.hpp
	$(CC) -c $(CFLAGS) -I$(INC) $< -o $@

$(OBJ)/compressUtility.o: $(SRC)/compressUtility.cpp $(INC)/compressUtility.hpp
	$(CC) -c $(CFLAGS) -I$(INC) $< -o $@

$(OBJ)/decompressUtility.o: $(SRC)/decompressUtility.cpp $(INC)/decompressUtility.hpp
	$(CC) -c $(CFLAGS) -I$(INC) $< -o $@

$(OBJ)/myVector.o: $(SRC)/myVector.cpp $(INC)/myVector.hpp
	$(CC) -c $(CFLAGS) -I$(INC) $< -o $@

$(OBJ)/myMap.o: $(SRC)/myMap.cpp $(INC)/myMap.hpp
	$(CC) -c $(CFLAGS) -I$(INC) $< -o $@

$(OBJ)/myPair.o: $(SRC)/myPair.cpp $(INC)/myPair.hpp
	$(CC) -c $(CFLAGS) -I$(INC) $< -o $@

runc: $(EXE)
	./$(EXE) -c $(file) compressed.bin

rund: $(EXE)
	./$(EXE) -d compressed.bin decompressed.txt

run: $(EXE)
	./$(EXE) -c atext.txt compressed.bin
	./$(EXE) -d compressed.bin decompressed.txt

clean:
	rm -f $(OBJS) $(EXE)
