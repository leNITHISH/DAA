#!/bin/bash

echo "rng2"

# Compile the necessary programs
g++ -o rnd rng2.cpp
g++ -o out merge.cpp

# Function to handle test cases
run_tests() {
  local mode=$1
  local start=$2
  local end=$3
  local step=$4

 # echo "$mode"
  for ((j = start; j < end; j += step)); do
    echo -e "$mode\n$j" | ./rnd
    ./out $j &
#    echo ""
  done
  wait
}

# Run tests for best, worst, and average cases
run_tests "best" 10000 100000 10000 &
run_tests "best" 100000 1000001 100000
wait
echo ""

# run_tests "worst" 10000 100000 10000
# run_tests "worst" 100000 1000001 100000
# echo ""

# run_tests "random" 10000 100000 10000
# run_tests "random" 100000 1000001 100000
# echo ""
