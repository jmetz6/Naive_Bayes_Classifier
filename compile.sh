#!/bin/bash

echo COMPILING

g++ -std=c++11 -c ./Sources/*.cpp

echo LINKING

g++ -o NaiveBayes.exe *.o

echo DONE