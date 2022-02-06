#!/bin/bash

./run_Genetic.sh 10 data/Falkenauer_T_60/ 42 5 > GENETIC_FALKENAUER.csv
./run_Genetic.sh 10 data/Schoenfield/ 42 5 > GENETIC_SCHOENFIELD.csv
./run_Genetic.sh 10 data/Scholl/easy/ 42 5 > GENETIC_SCHOLL_EASY.csv
./run_Genetic.sh 10 data/Scholl/medium/ 42 5 > GENETIC_SCHOLL_MEDIUM.csv

./run_GRASP.sh 10 data/Falkenauer_T_60/ 42 5 > GRASP_FALKENAUER.csv
./run_GRASP.sh 10 data/Schoenfield/ 42 5 > GRASP_SCHOENFIELD.csv
./run_GRASP.sh 10 data/Scholl/easy/ 42 5 > GRASP_SCHOLL_EASY.csv
./run_GRASP.sh 10 data/Scholl/medium/ 42 5 > GRASP_SCHOLL_MEDIUM.csv