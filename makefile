RM = rm -rf

CC=g++

INC_DIR=./include
SRC_DIR=./src
OBJ_DIR=./build
BIN_DIR=./bin

CFLAGS = -Wall -pedantic -ansi -std=c++17

all: dir ILS_driver Genetic_driver GRASP_driver

otimize: CFLAGS += -ftracer -Ofast
otimize: dir ILS_driver Genetic_driver GRASP_driver

debug: CFLAGS += -g -O0 -pg
debug: dir ILS_driver Genetic_driver GRASP_driver 

ILS_driver: $(OBJ_DIR)/ILS_driver.o $(OBJ_DIR)/ProblemInstance.o $(OBJ_DIR)/IteratedLocalSearch.o 
	$(CC) $(CFLAGS) -o $(BIN_DIR)/$@ $^

$(OBJ_DIR)/ILS_driver.o: $(SRC_DIR)/ILS_driver.cpp
	$(CC) -c $(CFLAGS) -I$(INC_DIR)/ -o $@ $<	

Genetic_driver: $(OBJ_DIR)/Genetic_driver.o $(OBJ_DIR)/ProblemInstance.o $(OBJ_DIR)/Genetic.o 
	$(CC) $(CFLAGS) -o $(BIN_DIR)/$@ $^

$(OBJ_DIR)/Genetic_driver.o: $(SRC_DIR)/Genetic_driver.cpp
	$(CC) -c $(CFLAGS) -I$(INC_DIR)/ -o $@ $<	

GRASP_driver: $(OBJ_DIR)/GRASP_driver.o $(OBJ_DIR)/ProblemInstance.o $(OBJ_DIR)/GRASP.o $(OBJ_DIR)/LocalSearch.o $(OBJ_DIR)/IteratedLocalSearch.o 
	$(CC) $(CFLAGS) -o $(BIN_DIR)/$@ $^

$(OBJ_DIR)/GRASP_driver.o: $(SRC_DIR)/GRASP_driver.cpp
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