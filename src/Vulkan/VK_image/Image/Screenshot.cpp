#include "Screenshot.h"

#include <Vulkan/Namespace.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <image/stb_image_write.h>
#include <fstream>
#include <iostream>


namespace vk::image{

//Constructor / Destructor
Screenshot::Screenshot(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_image = new vk::image::Image(vk_struct);
  this->vk_transition = new vk::image::Transition(vk_struct);
  this->vk_command_buffer = new vk::command::Command_buffer(vk_struct);
  this->vk_command_allocator = new vk::command::Allocator(vk_struct);
  this->vk_mem_transfer = new vk::memory::Transfer(vk_struct);
  this->vk_mem_allocator = new vk::memory::Allocator(vk_struct);

  //---------------------------
}
Screenshot::~Screenshot(){}

//Main function
void Screenshot::make_screenshot(){
  //---------------------------

  vk::structure::Renderpass* renderpass = vk_struct->render.get_renderpass_byName("edl");
  vk::structure::Image* image = &renderpass->framebuffer->color;
  this->export_image_to_bmp(image);

  //---------------------------
}
void Screenshot::export_image_to_jpeg(vk::structure::Image* image){
  //---------------------------

  //Create and fill stagging buffer
  VkBuffer staging_buffer;
  VkDeviceMemory staging_mem;
  VkDeviceSize tex_size = image->width * image->height * 4;
  vk_mem_allocator->create_gpu_buffer(tex_size, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_TRANSFER_SRC_BIT, staging_buffer);
  vk_mem_allocator->bind_buffer_memory(TYP_MEMORY_SHARED_CPU_GPU, staging_buffer, staging_mem);
  vk_mem_transfer->copy_image_to_buffer(image, staging_buffer);

  //Find image info
  VkExtent3D imageExtent = {image->width, image->height, 1};  // Replace with your image dimensions
  VkDeviceSize bufferSize = calculate_image_size(image->format, imageExtent);
  if(bufferSize == 0) return;

  //Save staging buffer data to file
  void* mappedData;
  vkMapMemory(vk_struct->device.handle, staging_mem, 0, bufferSize, 0, &mappedData);
  int channels = 4;  // Assuming RGBA data
  std::string filename = "temp.jpg";
  if(stbi_write_jpg(filename.c_str(), image->width, image->height, channels, mappedData, image->width * channels) == 0){
    throw std::runtime_error("Failed to write PNG file!");
  }
  vkUnmapMemory(vk_struct->device.handle, staging_mem);

  //Free memory
  vkDestroyBuffer(vk_struct->device.handle, staging_buffer, nullptr);
  vkFreeMemory(vk_struct->device.handle, staging_mem, nullptr);

  std::string finalFilename = "image.jpeg";
  std::rename(filename.c_str(), finalFilename.c_str()); // Rename temporary file to final filename

  //---------------------------
}
void Screenshot::export_image_to_bmp(vk::structure::Image* image){
  //---------------------------

  //Create and fill stagging buffer
  VkBuffer staging_buffer;
  VkDeviceMemory staging_mem;
  VkDeviceSize tex_size = image->width * image->height * 4;
  vk_mem_allocator->create_gpu_buffer(tex_size, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_TRANSFER_SRC_BIT, staging_buffer);
  vk_mem_allocator->bind_buffer_memory(TYP_MEMORY_SHARED_CPU_GPU, staging_buffer, staging_mem);
  vk_mem_transfer->copy_image_to_buffer(image, staging_buffer);

  //Find image info
  VkExtent3D imageExtent = {image->width, image->height, 1};  // Replace with your image dimensions
  VkDeviceSize bufferSize = calculate_image_size(image->format, imageExtent);
  if(bufferSize == 0) return;

  //Save staging buffer data to file
  void* mappedData;
  vkMapMemory(vk_struct->device.handle, staging_mem, 0, bufferSize, 0, &mappedData);
  int channels = 4;  // Assuming RGBA data
  std::string filename = "temp.bmp";
  if(stbi_write_bmp(filename.c_str(), image->width, image->height, channels, mappedData) == 0){
    cout<<"[error] Failed to write BMP file"<<endl;
    return;
  }

  vkUnmapMemory(vk_struct->device.handle, staging_mem);

  //Free memory
  vkDestroyBuffer(vk_struct->device.handle, staging_buffer, nullptr);
  vkFreeMemory(vk_struct->device.handle, staging_mem, nullptr);

  std::string finalFilename = "image.bmp";
  std::rename(filename.c_str(), finalFilename.c_str()); // Rename temporary file to final filename

  //---------------------------
}
void Screenshot::export_image_to_binary(vk::structure::Image* image){
  //---------------------------

  //Create and fill stagging buffer
  VkBuffer staging_buffer;
  VkDeviceMemory staging_mem;
  VkDeviceSize tex_size = image->width * image->height * 4;
  vk_mem_allocator->create_gpu_buffer(tex_size, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_TRANSFER_SRC_BIT, staging_buffer);
  vk_mem_allocator->bind_buffer_memory(TYP_MEMORY_SHARED_CPU_GPU, staging_buffer, staging_mem);
  vk_mem_transfer->copy_image_to_buffer(image, staging_buffer);

  //Find image info
  VkExtent3D imageExtent = {image->width, image->height, 1};  // Replace with your image dimensions
  VkDeviceSize bufferSize = calculate_image_size(image->format, imageExtent);

  //Save staging buffer data to file
  void* mappedData;
  void* pixelData = malloc(bufferSize);
  VkResult mapResult =vkMapMemory(vk_struct->device.handle, staging_mem, 0, bufferSize, 0, &mappedData);
  //  memcpy(pixelData, mappedData, static_cast<size_t>(tex_size));
  if(mapResult == VK_SUCCESS){
      // Use mappedData as needed

      FILE* file = fopen("truc.bin", "wb"); // Open the file for writing in binary mode
      if(file != NULL){
          size_t bytesWritten = fwrite(mappedData, 1, bufferSize, file); // Write the data to the file

          if(bytesWritten != bufferSize){
              // Handle error if not all bytes were written
              fprintf(stderr, "Error writing all bytes to file: %s\n", "truc.bin");
          }

          fclose(file); // Close the file
      }else{
          // Handle error if file cannot be opened
          fprintf(stderr, "Error opening file for writing: %s\n", "truc.bin");
      }

      vkUnmapMemory(vk_struct->device.handle, staging_mem);
  }else{
      // Handle error if memory mapping fails
      fprintf(stderr, "Error mapping memory: %d\n", mapResult);
  }

  //Free memory
  vkDestroyBuffer(vk_struct->device.handle, staging_buffer, nullptr);
  vkFreeMemory(vk_struct->device.handle, staging_mem, nullptr);

  //---------------------------
}

//Subfunction
VkDeviceSize Screenshot::calculate_image_size(VkFormat format, VkExtent3D extent){
  //---------------------------

  // Get the number of bytes per pixel for the specified format
  VkFormatProperties formatProperties;
  vkGetPhysicalDeviceFormatProperties(vk_struct->device.physical_device.handle, format, &formatProperties);

  if((formatProperties.linearTilingFeatures & VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT) == 0){
    // Format does not support linear tiling, use optimal tiling instead
    // You may need to handle this differently based on your specific requirements
    // In this example, we'll assume optimal tiling support
    vkGetPhysicalDeviceFormatProperties(vk_struct->device.physical_device.handle, format, &formatProperties);
  }

  VkDeviceSize bytesPerPixel = 0;

  switch (format){
    case VK_FORMAT_R8_UNORM:
      bytesPerPixel = 1;
      break;
    case VK_FORMAT_R8G8_UNORM:
      bytesPerPixel = 2;
      break;
    case VK_FORMAT_R8G8B8A8_UNORM:
      bytesPerPixel = 4;
      break;
    case VK_FORMAT_B8G8R8A8_UNORM:
      bytesPerPixel = 4;
      break;
    case VK_FORMAT_B8G8R8A8_SRGB:
      bytesPerPixel = 4;
      break;
    case VK_FORMAT_R8G8B8A8_SRGB:
      bytesPerPixel = 4;
      break;

    default:
      throw std::runtime_error("Unsupported image format");
      return 0;
  }

  // Calculate the size of the image buffer
  VkDeviceSize imageSize = bytesPerPixel * extent.width * extent.height * extent.depth;

  //---------------------------
  return imageSize;
}

}
