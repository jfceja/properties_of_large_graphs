#!/bin/bash

g++ -std=c++11 -Wall graph.cpp main.cpp barabasi_albert.cpp graph_algorithms.cpp -o RUN_ME.out
chmod +x RUN_ME.out
echo "Running the program..."
./RUN_ME.out
