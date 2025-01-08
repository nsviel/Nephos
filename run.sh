#!/bin/bash

current_dir=$PWD

# Clear the terminal screen
clear

# Check if an argument was passed
if [ "$1" == "binding" ]; then
    # If the first argument is "bindings", build the Python bindings
    echo "Building Python bindings..."

    # Make sure you are in the correct directory for bindings
    mkdir -p $current_dir/build
    cd $current_dir/build

    # Run cmake and make commands for Python bindings (replace with actual build commands)
    cmake .. && make -j20 && python3 ../binding/test.py

elif [ "$1" == "executable" ]; then
    # If the first argument is "executable", build and run the executable normally
    echo "Building and running the executable..."

    mkdir -p $current_dir/build
    cd $current_dir/build

    # Run cmake and make commands for the executable
    cmake -G Ninja .. && ninja -j20 && ./executable

else
    # Default behavior if no or unrecognized argument is provided
    echo "Usage: $0 [binding|executable]"
    exit 1
fi
