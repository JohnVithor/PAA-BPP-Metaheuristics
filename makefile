RM = rm -rf

CC=g++

INC_DIR=./include
SRC_DIR=./src
OBJ_DIR=./build
BIN_DIR=./bin

CFLAGS = -Wall -pedantic -ansi -std=c++17

all: dir driver

otimize: CFLAGS += -ftracer -Ofast
otimize: dir driver

debug: CFLAGS += -g -O0 -pg
debug: driver

driver: $(OBJ_DIR)/driver.o $(OBJ_DIR)/LocalSearch.o $(OBJ_DIR)/IteratedLocalSearch.o $(OBJ_DIR)/ProblemInstance.o $(OBJ_DIR)/Genetic.o $(OBJ_DIR)/GRASP.o
	$(CC) $(CFLAGS) -o $(BIN_DIR)/$@ $^

$(OBJ_DIR)/driver.o: $(SRC_DIR)/driver.cpp
	$(CC) -c $(CFLAGS) -I$(INC_DIR)/ -o $@ $<	

$(OBJ_DIR)/LocalSearch.o: $(SRC_DIR)/LocalSearch.cpp $(INC_DIR)/LocalSearch.hpp
	$(CC) -c $(CFLAGS) -I$(INC_DIR)/ -o $@ $<	

$(OBJ_DIR)/IteratedLocalSearch.o: $(SRC_DIR)/IteratedLocalSearch.cpp $(INC_DIR)/IteratedLocalSearch.hpp
	$(CC) -c $(CFLAGS) -I$(INC_DIR)/ -o $@ $<	

$(OBJ_DIR)/Genetic.o: $(SRC_DIR)/Genetic.cpp $(INC_DIR)/Genetic.hpp
	$(CC) -c $(CFLAGS) -I$(INC_DIR)/ -o $@ $<	

$(OBJ_DIR)/GRASP.o: $(SRC_DIR)/GRASP.cpp $(INC_DIR)/GRASP.hpp
	$(CC) -c $(CFLAGS) -I$(INC_DIR)/ -o $@ $<	

$(OBJ_DIR)/ProblemInstance.o: $(SRC_DIR)/ProblemInstance.cpp $(INC_DIR)/ProblemInstance.hpp
	$(CC) -c $(CFLAGS) -I$(INC_DIR)/ -o $@ $<

dir:
	mkdir -p bin build results
	
clean: dir
	$(RM) $(BIN_DIR)/*
	$(RM) $(OBJ_DIR)/*