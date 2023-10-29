#!/bin/bash

current_dir=$PWD

clear
mkdir -p $current_dir/build
cd $current_dir/build
cmake .. && make -j20 && ./executable
cd $current_dir
