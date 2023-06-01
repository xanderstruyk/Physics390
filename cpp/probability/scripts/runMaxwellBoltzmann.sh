#!/bin/sh

./bin/test_maxwell_boltzmann_rejection $RANDOM 1 > ./data/maxwell_boltzmann_rejection_1.dat

./bin/test_maxwell_boltzmann_rejection $RANDOM 2 > ./data/maxwell_boltzmann_rejection_2.dat

./bin/test_maxwell_boltzmann_rejection $RANDOM 5 > ./data/maxwell_boltzmann_rejection_5.dat


./bin/test_maxwell_boltzmann_rejection $RANDOM 1 > ./data/maxwell_boltzmann_metropolis_1.dat

./bin/test_maxwell_boltzmann_rejection $RANDOM 2 > ./data/maxwell_boltzmann_metropolis_2.dat

./bin/test_maxwell_boltzmann_rejection $RANDOM 5 > ./data/maxwell_boltzmann_metropolis_5.dat

