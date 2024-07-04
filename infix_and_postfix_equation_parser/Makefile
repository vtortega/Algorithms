CC = g++
CFLAGS = -Wall -Wextra -pedantic -g -std=c++11
LFLAGS = -lm
SRC = src
OBJ = obj
INC = include
BIN = bin
EXE = $(BIN)/program

OBJS = $(OBJ)/addnode.o $(OBJ)/binaryopnode.o $(OBJ)/dividenode.o \
	   $(OBJ)/multiplynode.o $(OBJ)/node.o $(OBJ)/parser.o \
	   $(OBJ)/subtractnode.o $(OBJ)/valuenode.o $(OBJ)/stack.o \
	   $(OBJ)/main.o

$(EXE): $(OBJS)
	$(CC) $(OBJS) -o $(EXE) $(LFLAGS)

$(OBJ)/main.o: $(SRC)/main.cpp $(INC)/node.hpp $(INC)/parser.hpp $(INC)/stack.hpp
	$(CC) -c $(CFLAGS) -I$(INC) $< -o $@

$(OBJ)/addnode.o: $(SRC)/addnode.cpp $(INC)/addnode.hpp $(INC)/binaryopnode.hpp $(INC)/node.hpp
	$(CC) -c $(CFLAGS) -I$(INC) $< -o $@

$(OBJ)/binaryopnode.o: $(SRC)/binaryopnode.cpp $(INC)/binaryopnode.hpp $(INC)/node.hpp
	$(CC) -c $(CFLAGS) -I$(INC) $< -o $@

$(OBJ)/dividenode.o: $(SRC)/dividenode.cpp $(INC)/dividenode.hpp $(INC)/binaryopnode.hpp $(INC)/node.hpp
	$(CC) -c $(CFLAGS) -I$(INC) $< -o $@

$(OBJ)/multiplynode.o: $(SRC)/multiplynode.cpp $(INC)/multiplynode.hpp $(INC)/binaryopnode.hpp $(INC)/node.hpp
	$(CC) -c $(CFLAGS) -I$(INC) $< -o $@

$(OBJ)/node.o: $(SRC)/node.cpp $(INC)/node.hpp
	$(CC) -c $(CFLAGS) -I$(INC) $< -o $@

$(OBJ)/parser.o: $(SRC)/parser.cpp $(INC)/parser.hpp $(INC)/node.hpp $(INC)/addnode.hpp $(INC)/subtractnode.hpp $(INC)/multiplynode.hpp $(INC)/dividenode.hpp $(INC)/valuenode.hpp
	$(CC) -c $(CFLAGS) -I$(INC) $< -o $@

$(OBJ)/stack.o: $(SRC)/stack.cpp $(INC)/stack.hpp
	$(CC) -c $(CFLAGS) -I$(INC) $< -o $@

$(OBJ)/subtractnode.o: $(SRC)/subtractnode.cpp $(INC)/subtractnode.hpp $(INC)/binaryopnode.hpp $(INC)/node.hpp
	$(CC) -c $(CFLAGS) -I$(INC) $< -o $@

$(OBJ)/valuenode.o: $(SRC)/valuenode.cpp $(INC)/valuenode.hpp $(INC)/node.hpp
	$(CC) -c $(CFLAGS) -I$(INC) $< -o $@

run: $(EXE)
	./$(EXE) $(file)

clean:
	rm -f $(OBJS) $(EXE)
