#!/bin/bash

# Nephos engine installation
# For now, this script only support apt package manager from ubuntu. For other linux related OS, try the following commands:

# Start
echo -ne "[\e[92m#\e[0m] Run installation for Ubuntu related OS..."

# Ubuntu
sudo apt install -y python3-pybind11 libhdf5-serial-dev curl
sudo apt install -y cmake build-essential libeigen3-dev python3-dev libsqlite3-dev sqlite3 git ffmpeg ninja-build
sudo apt install -y vulkan-tools libvulkan-dev spirv-tools lm-sensors libspdlog-dev
sudo apt install -y libglfw3-dev libxxf86vm-dev libxi-dev libavcodec-dev libavformat-dev libswscale-dev libvlc-dev
sudo apt install -y libglm-dev libgit2-dev libgtest-dev libtins-dev libavdevice-dev libudev-dev libturbojpeg-dev
sudo apt install -y libmatroska-dev nlohmann-json3-dev libopencv-dev libusb-1.0-0-dev libflann-dev nvidia-cuda-dev

# LunarG SDK
curl -fsSL https://packages.lunarg.com/lunarg-signing-key-pub.asc | sudo tee /etc/apt/trusted.gpg.d/lunarg-signing-key.asc
sudo wget -qO /etc/apt/sources.list.d/lunarg-vulkan-1.3.296-noble.list https://packages.lunarg.com/vulkan/1.3.296/lunarg-vulkan-1.3.296-noble.list
sudo apt update
sudo apt install vulkan-sdk

# Azur kinect SDK
cd extern/azur_sdk/
sudo ./install_azure_kinect_camera_u_22.04.sh
rm -f *.deb
cd ../..

#Intel realsense
sudo apt install libglfw3-dev libgl1-mesa-dev libglu1-mesa-dev
sudo apt install v4l-utils libgtk-3-dev libssl-dev
cd extern/realsense2/
git clone https://github.com/IntelRealSense/librealsense.git
cd librealsense
./scripts/setup_udev_rules.sh
cd ../../..

#Robin-map
sudo apt install -y robin-map-dev
git clone https://github.com/Tessil/robin-map.git
cd robin-map && mkdir build && cd build
cmake .. && make -j5 && sudo make install
cd ../.. && sudo rm -rf robin-map

# End
echo -ne "[\e[92m#\e[0m] Done"
