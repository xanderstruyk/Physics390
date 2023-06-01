#!/bin/sh

mkdir -p data/importance_example
mkdir -p png/importance_example

./bin/test_importance $RANDOM > ./data/importance_example/integrals.dat
