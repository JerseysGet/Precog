#!/usr/bin/bash

PWD=$(pwd)

CPP_FLAGS="-O2 -std=c++20 -fopenmp"
CPP_DEPS="$PWD/src/file_io/file_util.cpp $PWD/src/diameter/diameter.cpp $PWD/src/diameter/compute_diameter.cpp"
DIAMETER_INFO_FILE="$PWD/dataset/computed/diameter_info.txt"

if [ ! -f $DIAMETER_INFO_FILE ]; then
    echo "$DIAMETER_INFO_FILE not found, computing" 
    g++ $CPP_FLAGS $CPP_DEPS -o cc_compute.out
    time ./cc_compute.out $DIAMETER_INFO_FILE
    rm cc_compute.out
else 
    echo "$DIAMETER_INFO_FILE found"
fi

DIAMETER_VIZ_PATH="$PWD/src/diameter/diameter_viz.py"

python3 $DIAMETER_VIZ_PATH $DIAMETER_INFO_FILE

