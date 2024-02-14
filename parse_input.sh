#!/usr/bin/bash

PWD=$(pwd)


GRAPH_INPUT_FILE="$PWD/dataset/graph_input.txt"
DATE_INPUT_FILE="$PWD/dataset/date_input.txt"
PRETIME_INPUT_DIR="$PWD/dataset/pretime"

python src/file_io/generate_input.py $GRAPH_INPUT_FILE $DATE_INPUT_FILE
python src/file_io/generate_time_graphs.py $GRAPH_INPUT_FILE $DATE_INPUT_FILE $PRETIME_INPUT_DIR