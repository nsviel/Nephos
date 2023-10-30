#!/bin/bash

# Nephos engine installation
# For now, this script only support apt package manager from ubuntu. For other linux related OS, try the following commands:


echo -ne "[\e[92m#\e[0m] Run installation for Ubuntu related OS..."

# Ubuntu
sudo apt install -y cmake build-essential libeigen3-dev python3-dev libsqlite3-dev sqlite3 git ffmpeg
sudo apt install -y vulkan-tools libvulkan-dev vulkan-validationlayers-dev spirv-tools
sudo apt install -y libglfw3-dev libxxf86vm-dev libxi-dev libavcodec-dev libavformat-dev libswscale-dev libvlc-dev
sudo apt install -y libglm-dev libgit2-dev libgtest-dev libtins-dev

# LunarG SDK
wget -qO- https://packages.lunarg.com/lunarg-signing-key-pub.asc | sudo tee /etc/apt/trusted.gpg.d/lunarg.asc
sudo wget -qO /etc/apt/sources.list.d/lunarg-vulkan-1.3.243-jammy.list https://packages.lunarg.com/vulkan/1.3.243/lunarg-vulkan-1.3.243-jammy.list
sudo apt update
sudo apt -y install vulkan-sdk



echo -ne "[\e[92m#\e[0m] Done"
