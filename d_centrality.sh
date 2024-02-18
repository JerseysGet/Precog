
PWD=$(pwd)

CPP_FLAGS="-O2 -std=c++20"
CPP_DEPS="$PWD/src/file_io/file_util.cpp $PWD/src/centrality/d_centrality.cpp $PWD/src/centrality/compute_d_centrality.cpp"
D_INFO_FILE="$PWD/dataset/computed/d_centrality_info.txt"

if [ ! -f $D_INFO_FILE ]; then
    echo "$D_INFO_FILE not found, computing" 
    g++ $CPP_FLAGS $CPP_DEPS -o d_compute.out
    ./d_compute.out > $D_INFO_FILE
    rm d_compute.out
else 
    echo "$D_INFO_FILE found"
fi

D_VISUALIZER_PATH="$PWD/src/centrality/d_centrality.py"

python3 $D_VISUALIZER_PATH $D_INFO_FILE