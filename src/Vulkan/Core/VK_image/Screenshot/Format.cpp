#include "Format.h"

#include <Vulkan/Namespace.h>
#include <image/stb_image_write.h>
#include <fstream>
#include <iostream>


namespace vk::screenshot{

//Constructor / Destructor
Format::Format(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;

  //---------------------------
}
Format::~Format(){}

//Main function
void Format::export_to_format(vk::structure::Image& image, void* data){
  //---------------------------

  switch(vk_struct->core.image.screenshot_format){
    case vk::screenshot::BMP:
      this->export_to_bmp(image, data);
      break;
    case vk::screenshot::JPEG:
      this->export_to_jpeg(image, data);
      break;
    case vk::screenshot::BIN:
      this->export_to_bin(image, data);
      break;
  }

  //---------------------------
}

//Subfunction
void Format::export_to_jpeg(vk::structure::Image& image, void* data){
  //---------------------------

  std::string filename = "image.jpg";
  if(stbi_write_jpg(filename.c_str(), image.width, image.height, image.channel_nb, data, image.width * image.channel_nb) == 0){
    throw std::runtime_error("[error] Failed to write JPEG file");
  }

  //---------------------------
}
void Format::export_to_bmp(vk::structure::Image& image, void* data){
  //---------------------------



  std::string filename = "image.bmp";
  if(stbi_write_bmp(filename.c_str(), image.width, image.height, image.channel_nb, data) == 0){
    std::cout<<"[error] Failed to write BMP file"<<std::endl;
    return;
  }

  //---------------------------
}
void Format::export_to_bin(vk::structure::Image& image, void* data){
  //---------------------------

  VkDeviceSize bufferSize = image.height * image.width * image.channel_nb;

  FILE* file = fopen("truc.bin", "wb"); // Open the file for writing in binary mode
  if(file != NULL){
    size_t bytesWritten = fwrite(data, 1, bufferSize, file); // Write the data to the file

    if(bytesWritten != bufferSize){
      // Handle error if not all bytes were written
      fprintf(stderr, "Error writing all bytes to file: %s\n", "truc.bin");
    }

    fclose(file); // Close the file
  }else{
    // Handle error if file cannot be opened
    fprintf(stderr, "Error opening file for writing: %s\n", "truc.bin");
  }

  //---------------------------
}

}
