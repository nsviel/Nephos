#include "Screenshot.h"

#include <Vulkan/Namespace.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <image/stb_image_write.h>


namespace vk::image{

//Constructor / Destructor
Screenshot::Screenshot(vk::structure::Vulkan* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_image = new vk::image::Image(vk_struct);
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

  vk::structure::Renderpass* renderpass = vk_struct->render.vec_renderpass[1];
  vk::structure::Image image = renderpass->framebuffer->color;
  this->export_image_to_jpeg(&image);

  //---------------------------
}
void Screenshot::export_image_to_jpeg(vk::structure::Image* image){
  //---------------------------

  //Create stagging buffer
  VkBuffer staging_buffer;
  VkDeviceMemory staging_mem;
  VkDeviceSize tex_size = image->width * image->height * 4;
  vk_mem_allocator->create_gpu_buffer(tex_size, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_TRANSFER_SRC_BIT, staging_buffer);
  vk_mem_allocator->bind_buffer_memory(TYP_MEMORY_SHARED_CPU_GPU, staging_buffer, staging_mem);



  //Image transition from undefined layout to read only layout
  vk::pool::Command_buffer* pool = vk_command_allocator->query_free_pool(&vk_struct->device.queue.graphics);
  vk::structure::Command_buffer* command_buffer = vk_command_buffer->query_free_command_buffer(pool);
  command_buffer->name = "Screenshot";
  vk_command_buffer->start_command_buffer_primary(command_buffer);

  // Image transition to transfer source optimal layout
  vk_image->image_layout_transition(command_buffer->command, image, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL);
  vk_mem_transfer->copy_image_to_buffer(command_buffer, image, staging_buffer);
  vk_image->image_layout_transition(command_buffer->command, image, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);

  vk_command_buffer->end_command_buffer(command_buffer);

  vk::structure::Command* command = new vk::structure::Command();
  command->vec_command_buffer.push_back(command_buffer);
  vk_struct->queue.graphics->add_command(command);




  VkExtent3D imageExtent = {image->width, image->height, 1};  // Replace with your image dimensions
  VkDeviceSize bufferSize = calculate_image_size(image->format, imageExtent);
  if(bufferSize == 0) return;

  // 3. Save staging buffer data to file
  void* mappedData;
  vkMapMemory(vk_struct->device.handle, staging_mem, 0, bufferSize, 0, &mappedData);
  int channels = 4;  // Assuming RGBA data, adjust as needed
  std::string filename = "output.jpg";  // Adjust the file name and format as needed
  if (stbi_write_jpg(filename.c_str(), image->width, image->height, channels, mappedData, image->width * channels) == 0) {
    throw std::runtime_error("Failed to write PNG file!");
  }
  vkUnmapMemory(vk_struct->device.handle, staging_mem);

  //Free memory
  vkDestroyBuffer(vk_struct->device.handle, staging_buffer, nullptr);
  vkFreeMemory(vk_struct->device.handle, staging_mem, nullptr);

  //---------------------------
}
void Screenshot::export_image_to_binary(vk::structure::Image* image){
  //---------------------------

  //Create stagging buffer
  VkBuffer staging_buffer;
  VkDeviceMemory staging_mem;
  VkDeviceSize tex_size = image->width * image->height * 4;
  vk_mem_allocator->create_gpu_buffer(tex_size, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_TRANSFER_SRC_BIT, staging_buffer);
  vk_mem_allocator->bind_buffer_memory(TYP_MEMORY_SHARED_CPU_GPU, staging_buffer, staging_mem);

  //Image transition from undefined layout to read only layout
  vk::pool::Command_buffer* pool = vk_command_allocator->query_free_pool(&vk_struct->device.queue.transfer);
  vk::structure::Command_buffer* command_buffer = vk_command_buffer->query_free_command_buffer(pool);
  command_buffer->name = "Screenshot";
  vk_command_buffer->start_command_buffer_primary(command_buffer);

  vk_image->image_layout_transition(command_buffer->command, image, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL);
  vk_mem_transfer->copy_image_to_buffer(command_buffer, image, staging_buffer);

  vk_command_buffer->end_command_buffer(command_buffer);
  vk_struct->queue.transfer->add_command(command_buffer);




  VkExtent3D imageExtent = {image->width, image->height, 1};  // Replace with your image dimensions
  VkDeviceSize bufferSize = calculate_image_size(image->format, imageExtent);

  // 3. Save staging buffer data to file
  void* mappedData;
  void* pixelData = malloc(bufferSize);
  VkResult mapResult =vkMapMemory(vk_struct->device.handle, staging_mem, 0, bufferSize, 0, &mappedData);
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

      vkUnmapMemory(vk_struct->device.handle, staging_mem);
  } else {
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

  if ((formatProperties.linearTilingFeatures & VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT) == 0) {
    // Format does not support linear tiling, use optimal tiling instead
    // You may need to handle this differently based on your specific requirements
    // In this example, we'll assume optimal tiling support
    vkGetPhysicalDeviceFormatProperties(vk_struct->device.physical_device.handle, format, &formatProperties);
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
