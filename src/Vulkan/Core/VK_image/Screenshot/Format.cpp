#include "Format.h"

#include <Vulkan/Namespace.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <image/stb_image_write.h>
#include <fstream>
#include <iostream>


namespace vk::screenshot{

//Constructor / Destructor
Format::Format(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_image = new vk::image::Image(vk_struct);
  this->vk_command_buffer = new vk::commandbuffer::Pool(vk_struct);
  this->vk_allocator = new vk::commandbuffer::Allocator(vk_struct);
  this->vk_mem_transfer = new vk::memory::Transfer(vk_struct);
  this->vk_mem_allocator = new vk::memory::Allocator(vk_struct);

  //---------------------------
}
Format::~Format(){}

//Main function
void Format::export_image_to_jpeg(vk::structure::Image& image){
  //---------------------------

  //Create and fill stagging buffer
  VkBuffer staging_buffer;
  VkDeviceMemory staging_mem;
  VkDeviceSize tex_size = image.width * image.height * 4;
  vk_mem_allocator->create_gpu_buffer(tex_size, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_TRANSFER_SRC_BIT, staging_buffer);
  vk_mem_allocator->bind_buffer_memory(TYP_MEMORY_SHARED_CPU_GPU, staging_buffer, staging_mem);
  vk_mem_transfer->copy_gpu_image_to_buffer(image, staging_buffer);

  //Find image info
  VkExtent3D imageExtent = {image.width, image.height, 1};  // Replace with your image dimensions
  VkDeviceSize bufferSize = calculate_image_size(image.format, imageExtent);
  if(bufferSize == 0) return;

  //Save staging buffer data to file
  void* mappedData;
  vkMapMemory(vk_struct->core.device.handle, staging_mem, 0, bufferSize, 0, &mappedData);

  int channels = 4;  // Assuming RGBA data
  std::string filename = "temp.jpg";
  if(stbi_write_jpg(filename.c_str(), image.width, image.height, channels, mappedData, image.width * channels) == 0){
    throw std::runtime_error("Failed to write PNG file!");
  }

  vkUnmapMemory(vk_struct->core.device.handle, staging_mem);

  //Free memory
  vkDestroyBuffer(vk_struct->core.device.handle, staging_buffer, nullptr);
  vkFreeMemory(vk_struct->core.device.handle, staging_mem, nullptr);

  std::string finalFilename = "image.jpeg";
  std::rename(filename.c_str(), finalFilename.c_str()); // Rename temporary file to final filename

  //---------------------------
}
void Format::export_image_to_bmp(vk::structure::Image& image){
  //---------------------------

  //Create and fill stagging buffer
  VkBuffer staging_buffer;
  VkDeviceMemory staging_mem;
  VkDeviceSize tex_size = image.width * image.height * 4;
  vk_mem_allocator->create_gpu_buffer(tex_size, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_TRANSFER_SRC_BIT, staging_buffer);
  vk_mem_allocator->bind_buffer_memory(TYP_MEMORY_SHARED_CPU_GPU, staging_buffer, staging_mem);
  vk_mem_transfer->copy_gpu_image_to_buffer(image, staging_buffer);

  //Find image info
  VkExtent3D imageExtent = {image.width, image.height, 1};  // Replace with your image dimensions
  VkDeviceSize bufferSize = calculate_image_size(image.format, imageExtent);
  if(bufferSize == 0) return;

  //Save staging buffer data to file
  void* mappedData;
  vkMapMemory(vk_struct->core.device.handle, staging_mem, 0, bufferSize, 0, &mappedData);

  // Invert red and green channels
  unsigned char* pixelData = static_cast<unsigned char*>(mappedData);
  for(int i = 0; i < image.width * image.height; i++){
    // RGBA format: pixelData[4 * i] = R, pixelData[4 * i + 1] = G, pixelData[4 * i + 2] = B, pixelData[4 * i + 3] = A
    std::swap(pixelData[4 * i], pixelData[4 * i + 2]);  // Swap R (index 0) and G (index 1)
  }

  int channels = 4;  // Assuming RGBA data
  std::string filename = "temp.bmp";
  if(stbi_write_bmp(filename.c_str(), image.width, image.height, channels, mappedData) == 0){
    std::cout<<"[error] Failed to write BMP file"<<std::endl;
    return;
  }

  vkUnmapMemory(vk_struct->core.device.handle, staging_mem);

  //Free memory
  vkDestroyBuffer(vk_struct->core.device.handle, staging_buffer, nullptr);
  vkFreeMemory(vk_struct->core.device.handle, staging_mem, nullptr);

  std::string finalFilename = "image.bmp";
  std::rename(filename.c_str(), finalFilename.c_str()); // Rename temporary file to final filename

  //---------------------------
}
void Format::export_depth_to_bmp(vk::structure::Image& image){
  //---------------------------

  //Create and fill stagging buffer
  VkBuffer staging_buffer;
  VkDeviceMemory staging_mem;
  VkDeviceSize tex_size = image.width * image.height * sizeof(float);;
  vk_mem_allocator->create_gpu_buffer(tex_size, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_TRANSFER_SRC_BIT, staging_buffer);
  vk_mem_allocator->bind_buffer_memory(TYP_MEMORY_SHARED_CPU_GPU, staging_buffer, staging_mem);
  vk_mem_transfer->copy_gpu_depth_to_buffer(image, staging_buffer);

  //Find image info
  VkExtent3D imageExtent = {image.width, image.height, 1};  // Replace with your image dimensions
  VkDeviceSize bufferSize = calculate_image_size(image.format, imageExtent);
  if(bufferSize == 0) return;

  //Save staging buffer data to file
  void* mappedData;
  vkMapMemory(vk_struct->core.device.handle, staging_mem, 0, bufferSize, 0, &mappedData);

  // Normalize depth data to 8-bit grayscale
  float* depthData = static_cast<float*>(mappedData);
  std::vector<uint8_t> grayscaleData(image.width * image.height);
  for (uint32_t i = 0; i < image.width * image.height; ++i) {
      float depth = depthData[i];
      grayscaleData[i] = static_cast<uint8_t>(std::clamp(depth * 255.0f, 0.0f, 255.0f)); // Normalize depth to 0-255
  }


  // Write to BMP
  std::string filename = "depth_image.bmp";
  if (stbi_write_bmp(filename.c_str(), image.width, image.height, 1, grayscaleData.data()) == 0) {
      std::cout << "[error] Failed to write BMP file" << std::endl;
      return;
  }

  vkUnmapMemory(vk_struct->core.device.handle, staging_mem);

  // Free memory
  vkDestroyBuffer(vk_struct->core.device.handle, staging_buffer, nullptr);
  vkFreeMemory(vk_struct->core.device.handle, staging_mem, nullptr);


  std::string finalFilename = "image.bmp";
  std::rename(filename.c_str(), finalFilename.c_str()); // Rename temporary file to final filename

  //---------------------------
}
void Format::export_image_to_binary(vk::structure::Image& image){
  //---------------------------

  //Create and fill stagging buffer
  VkBuffer staging_buffer;
  VkDeviceMemory staging_mem;
  VkDeviceSize tex_size = image.width * image.height * 4;
  vk_mem_allocator->create_gpu_buffer(tex_size, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_TRANSFER_SRC_BIT, staging_buffer);
  vk_mem_allocator->bind_buffer_memory(TYP_MEMORY_SHARED_CPU_GPU, staging_buffer, staging_mem);
  vk_mem_transfer->copy_gpu_image_to_buffer(image, staging_buffer);

  //Find image info
  VkExtent3D imageExtent = {image.width, image.height, 1};  // Replace with your image dimensions
  VkDeviceSize bufferSize = calculate_image_size(image.format, imageExtent);

  //Save staging buffer data to file
  void* mappedData;
  void* pixelData = malloc(bufferSize);
  VkResult mapResult =vkMapMemory(vk_struct->core.device.handle, staging_mem, 0, bufferSize, 0, &mappedData);
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

      vkUnmapMemory(vk_struct->core.device.handle, staging_mem);
  }else{
      // Handle error if memory mapping fails
      fprintf(stderr, "Error mapping memory: %d\n", mapResult);
  }

  //Free memory
  vkDestroyBuffer(vk_struct->core.device.handle, staging_buffer, nullptr);
  vkFreeMemory(vk_struct->core.device.handle, staging_mem, nullptr);

  //---------------------------
}

//Subfunction
VkDeviceSize Format::calculate_image_size(VkFormat format, VkExtent3D extent){
  //---------------------------

  // Get the number of bytes per pixel for the specified format
  VkFormatProperties formatProperties;
  vkGetPhysicalDeviceFormatProperties(vk_struct->core.device.physical_device.handle, format, &formatProperties);

  if((formatProperties.linearTilingFeatures & VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT) == 0){
    // Format does not support linear tiling, use optimal tiling instead
    // You may need to handle this differently based on your specific requirements
    // In this example, we'll assume optimal tiling support
    vkGetPhysicalDeviceFormatProperties(vk_struct->core.device.physical_device.handle, format, &formatProperties);
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
    case VK_FORMAT_R8G8B8A8_SRGB:
      bytesPerPixel = 4;
      break;

    // Add case for depth formats
    case VK_FORMAT_D32_SFLOAT:
    case VK_FORMAT_D32_SFLOAT_S8_UINT:
    case VK_FORMAT_D24_UNORM_S8_UINT:
    case VK_FORMAT_S8_UINT:
      bytesPerPixel = 4; // Typically, depth formats are 4 bytes (float or int)
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
