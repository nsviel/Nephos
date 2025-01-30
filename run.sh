#!/bin/bash

current_dir=$PWD

# Clear the terminal screen
clear

# Check if an argument was passed
if [ "$1" == "python" ]; then
    # If the first argument is "bindings", build the Python bindings
    echo "Building Python bindings..."

    # Make sure you are in the correct directory for bindings
    mkdir -p $current_dir/build
    cd $current_dir/build

    # Run cmake and make commands for Python bindings (replace with actual build commands)
    #export PYTHONPATH=$PYTHONPATH:$(pwd)/build
    #cmake -G Ninja .. && ninja -j20 && python ../cmake/Python/test.py
    cmake -G Ninja .. && ninja -j20 #&& python -m pip install ../cmake/Python


elif [ "$1" == "cmake" ]; then
    # If the first argument is "bindings", build the Python bindings
    echo "Building with CMake..."

    mkdir -p $current_dir/build
    cd $current_dir/build

    # Run cmake and make commands for the executable
    cmake .. && make -j20 && ./executable

else
    # If the first argument is "executable", build and run the executable normally
    echo "Building and running the executable..."

    mkdir -p $current_dir/build
    cd $current_dir/build

    # Run cmake and make commands for the executable
    cmake -G Ninja .. && ninja -j20 && ./executable
fi
