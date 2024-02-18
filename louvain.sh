#!/usr/bin/bash

PWD=$(pwd)

CPP_FLAGS="-O2 -std=c++20"
CPP_DEPS="$PWD/src/file_io/file_util.cpp $PWD/src/community_detection/partition.cpp $PWD/src/community_detection/louvain.cpp"
L_INFO_FILE="$PWD/dataset/computed/louvain_count.txt"

if [ ! -f $L_INFO_FILE ]; then
    echo "$L_INFO_FILE not found, computing" 
    g++ $CPP_FLAGS $CPP_DEPS -o l_compute.out
    time ./l_compute.out $L_INFO_FILE > $L_INFO_FILE
    rm l_compute.out
else 
    echo "$L_INFO_FILE found"
fi

B_VISUALIZER_PATH="$PWD/src/community_detection/louvain.py"

python3 $B_VISUALIZER_PATH $L_INFO_FILE