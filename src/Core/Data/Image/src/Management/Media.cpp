#include "Media.h"

#define STB_IMAGE_IMPLEMENTATION
#include <image/stb_image.h>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>


namespace dat::img{

void load_image_data(utl::media::Image& image, std::string path){
  //---------------------------

  uint8_t* data = stbi_load(path.c_str(), &image.width, &image.height, &image.channel_nb, STBI_rgb_alpha);

  size_t size = static_cast<size_t>(image.width) * static_cast<size_t>(image.height) * static_cast<size_t>(image.channel_nb);
  image.data = std::vector<uint8_t>(data, data + size);
  image.size = image.data.size();
  if(image.data.empty()){
    std::cout<<"[error] failed to load texture image"<<std::endl;
  }

  stbi_image_free(data);

  if(image.channel_nb == 3) dat::img::add_alpha_channel(image);

  //---------------------------
}
bool is_device_connected(const std::string& devicePath){
  //---------------------------

  int fileDescriptor = open(devicePath.c_str(), O_RDONLY);

  if(fileDescriptor == -1){
    // Failed to open the device file
    return false;
  }

  close(fileDescriptor);  // Close the file descriptor

  //---------------------------
  return true;
}
void add_alpha_channel(utl::media::Image& image){
  //---------------------------

  std::vector<uint8_t> new_data;
  new_data.reserve(image.width * image.height * 4); // Reserve space for RGBA

  for (int i = 0; i < image.data.size(); i += 3) {
    // Copy RGB values
    new_data.push_back(image.data[i]);     // R
    new_data.push_back(image.data[i + 1]); // G
    new_data.push_back(image.data[i + 2]); // B
    new_data.push_back(255);               // A (fully opaque)
  }

  // Replace the old data with the new RGBA data
  image.data = std::move(new_data);
  image.size = image.data.size();
  
  //---------------------------
}

}
