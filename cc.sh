#!/usr/bin/bash

PWD=$(pwd)

CPP_FLAGS="-O2 -std=c++20"
CPP_DEPS="$PWD/src/file_io/file_util.cpp $PWD/src/cc_variation/cc.cpp $PWD/src/cc_variation/compute_cc.cpp"
CC_INFO_FILE="$PWD/dataset/computed/cc_info.txt"

if [ ! -f $CC_INFO_FILE ]; then
    echo "$CC_INFO_FILE not found, computing" 
    g++ $CPP_FLAGS $CPP_DEPS -o cc_compute.out
    ./cc_compute.out $CC_INFO_FILE
    rm cc_compute.out
else 
    echo "$CC_INFO_FILE found"
fi

CC_VISUALIZER_PATH="$PWD/src/cc_variation/cc_count.py"

python3 $CC_VISUALIZER_PATH $CC_INFO_FILE
