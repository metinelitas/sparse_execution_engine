# sparse_execution_engine


## Build 
Run following commands from main folder

### Build using CMake

    mkdir build 
    cd build
    cmake -DCMAKE_BUILD_TYPE=Release ..
    make

### Build using g++

    mkdir build
    g++ --std=c++11 src/main.cc -o build/sparse_execution_engine

## Run

    ./build/sparse_execution_engine
