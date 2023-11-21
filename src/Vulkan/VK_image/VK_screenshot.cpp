#include "VK_screenshot.h"
#include "VK_texture.h"

#include <VK_image/VK_image.h>
#include <VK_main/Struct_vulkan.h>
#include <VK_data/VK_buffer.h>
#include <VK_command/VK_command.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <image/stb_image_write.h>


//Constructor / Destructor
VK_screenshot::VK_screenshot(Struct_vulkan* struct_vulkan){
  //---------------------------

  this->struct_vulkan = struct_vulkan;
  this->vk_buffer = new VK_buffer(struct_vulkan);
  this->vk_image = new VK_image(struct_vulkan);
  this->vk_command = new VK_command(struct_vulkan);
  this->vk_texture = new VK_texture(struct_vulkan);

  //---------------------------
}
VK_screenshot::~VK_screenshot(){}

//Main function
void VK_screenshot::make_screenshot(Struct_vk_image* image){
  //---------------------------

  //Create stagging buffer
  VkBuffer staging_buffer;
  VkDeviceMemory staging_mem;
  VkDeviceSize tex_size = image->width * image->height * 4;
  vk_buffer->create_gpu_buffer(tex_size, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_TRANSFER_SRC_BIT, staging_buffer);
  vk_buffer->bind_buffer_memory(TYP_MEMORY_SHARED_CPU_GPU, staging_buffer, staging_mem);

  vk_command->image_layout_transition_single(image, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL);
  vk_texture->copy_image_to_buffer(image, staging_buffer);

  VkExtent3D imageExtent = {image->width, image->height, 1};  // Replace with your image dimensions
  VkDeviceSize bufferSize = calculate_image_size(image->format, imageExtent);

  // 3. Save staging buffer data to file
  void* mappedData;
  vkMapMemory(struct_vulkan->device.device, staging_mem, 0, bufferSize, 0, &mappedData);
  int channels = 4;  // Assuming RGBA data, adjust as needed
  std::string filename = "output.jpg";  // Adjust the file name and format as needed
  if (stbi_write_jpg(filename.c_str(), image->width, image->height, channels, mappedData, image->width * channels) == 0) {
    throw std::runtime_error("Failed to write PNG file!");
}
  vkUnmapMemory(struct_vulkan->device.device, staging_mem);

  //Free memory
  vkDestroyBuffer(struct_vulkan->device.device, staging_buffer, nullptr);
  vkFreeMemory(struct_vulkan->device.device, staging_mem, nullptr);

  //---------------------------
}
void VK_screenshot::save_to_bin(Struct_vk_image* image){
  //---------------------------

  //Create stagging buffer
  VkBuffer staging_buffer;
  VkDeviceMemory staging_mem;
  VkDeviceSize tex_size = image->width * image->height * 4;
  vk_buffer->create_gpu_buffer(tex_size, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_TRANSFER_SRC_BIT, staging_buffer);
  vk_buffer->bind_buffer_memory(TYP_MEMORY_SHARED_CPU_GPU, staging_buffer, staging_mem);

  vk_command->image_layout_transition_single(image, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL);
  vk_texture->copy_image_to_buffer(image, staging_buffer);

  VkExtent3D imageExtent = {image->width, image->height, 1};  // Replace with your image dimensions
  VkDeviceSize bufferSize = calculate_image_size(image->format, imageExtent);

  // 3. Save staging buffer data to file
  void* mappedData;
  void* pixelData = malloc(bufferSize);
  VkResult mapResult =vkMapMemory(struct_vulkan->device.device, staging_mem, 0, bufferSize, 0, &mappedData);
  //  memcpy(pixelData, mappedData, static_cast<size_t>(tex_size));

  if (mapResult == VK_SUCCESS) {
      // Use mappedData as needed

      FILE* file = fopen("truc.bin", "wb"); // Open the file for writing in binary mode
      if (file != NULL) {
          size_t bytesWritten = fwrite(mappedData, 1, bufferSize, file); // Write the data to the file

          if (bytesWritten != bufferSize) {
              // Handle error if not all bytes were written
              fprintf(stderr, "Error writing all bytes to file: %s\n", "truc.bin");
          }

          fclose(file); // Close the file
      } else {
          // Handle error if file cannot be opened
          fprintf(stderr, "Error opening file for writing: %s\n", "truc.bin");
      }

      vkUnmapMemory(struct_vulkan->device.device, staging_mem);
  } else {
      // Handle error if memory mapping fails
      fprintf(stderr, "Error mapping memory: %d\n", mapResult);
  }

  //Free memory
  vkDestroyBuffer(struct_vulkan->device.device, staging_buffer, nullptr);
  vkFreeMemory(struct_vulkan->device.device, staging_mem, nullptr);

  //---------------------------
}

//Subfunction
VkDeviceSize VK_screenshot::calculate_image_size(VkFormat format, VkExtent3D extent){
  //---------------------------

  // Get the number of bytes per pixel for the specified format
  VkFormatProperties formatProperties;
  vkGetPhysicalDeviceFormatProperties(struct_vulkan->device.struct_device.physical_device, format, &formatProperties);

  if ((formatProperties.linearTilingFeatures & VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT) == 0) {
    // Format does not support linear tiling, use optimal tiling instead
    // You may need to handle this differently based on your specific requirements
    // In this example, we'll assume optimal tiling support
    vkGetPhysicalDeviceFormatProperties(struct_vulkan->device.struct_device.physical_device, format, &formatProperties);
  }

  VkDeviceSize bytesPerPixel = 0;

  switch (format) {
    case VK_FORMAT_R8_UNORM:
      bytesPerPixel = 1;
      break;
    case VK_FORMAT_R8G8_UNORM:
      bytesPerPixel = 2;
      break;
    case VK_FORMAT_R8G8B8A8_UNORM:
      bytesPerPixel = 4;
      break;
    // Add more cases for other formats as needed

    default:
      throw std::runtime_error("Unsupported image format");
  }

  // Calculate the size of the image buffer
  VkDeviceSize imageSize = bytesPerPixel * extent.width * extent.height * extent.depth;

  //---------------------------
  return imageSize;
}
