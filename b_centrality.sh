#!/usr/bin/bash

PWD=$(pwd)

CPP_FLAGS="-O2 -std=c++20 -fopenmp"
CPP_DEPS="$PWD/src/file_io/file_util.cpp $PWD/src/centrality/b_centrality.cpp $PWD/src/centrality/compute_b_centrality.cpp"
B_INFO_FILE="$PWD/dataset/computed/b_centrality_info.txt"

if [ ! -f $B_INFO_FILE ]; then
    echo "$B_INFO_FILE not found, computing" 
    g++ $CPP_FLAGS $CPP_DEPS -o b_compute.out
    time ./b_compute.out $B_INFO_FILE > $B_INFO_FILE
    rm b_compute.out
else 
    echo "$B_INFO_FILE found"
fi

B_VISUALIZER_PATH="$PWD/src/centrality/b_centrality.py"

python3 $B_VISUALIZER_PATH $B_INFO_FILE