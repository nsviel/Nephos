#include "VK_memory.h"

#include <VK_main/Struct_vulkan.h>
#include <VK_data/VK_buffer.h>
#include <VK_command/VK_command.h>


//Constructor / Destructor
VK_memory::VK_memory(Struct_vulkan* struct_vulkan){
  //---------------------------

  this->struct_vulkan = struct_vulkan;
  this->vk_buffer = new VK_buffer(struct_vulkan);
  this->vk_command = new VK_command(struct_vulkan);

  //---------------------------
}
VK_memory::~VK_memory(){}

//Main function
void VK_memory::transfert_image_to_gpu(Struct_vk_image* image){
  //---------------------------

  //Create stagging buffer
  VkBuffer staging_buffer;
  VkDeviceMemory staging_mem;
  VkDeviceSize tex_size = image->width * image->height * 4;
  vk_buffer->create_gpu_buffer(tex_size, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, staging_buffer);
  vk_buffer->bind_buffer_memory(TYP_MEMORY_SHARED_CPU_GPU, staging_buffer, staging_mem);

  //Copy data to stagging buffer
  void* data;
  vkMapMemory(struct_vulkan->device.device, staging_mem, 0, tex_size, 0, &data);
  memcpy(data, image->data, static_cast<size_t>(tex_size));
  vkUnmapMemory(struct_vulkan->device.device, staging_mem);

  //Image transition from undefined layout to read only layout
  vk_command->image_layout_transition_single(image, TYP_IMAGE_LAYOUT_EMPTY, TYP_IMAGE_LAYOUT_TRANSFER_DST);
  this->copy_buffer_to_image(image, staging_buffer);
  vk_command->image_layout_transition_single(image, TYP_IMAGE_LAYOUT_TRANSFER_DST, TYP_IMAGE_LAYOUT_SHADER_READONLY);

  //Free memory
  vkDestroyBuffer(struct_vulkan->device.device, staging_buffer, nullptr);
  vkFreeMemory(struct_vulkan->device.device, staging_mem, nullptr);

  //---------------------------
}
void VK_memory::copy_buffer_to_image(Struct_vk_image* image, VkBuffer buffer){
  //---------------------------

  VkCommandBuffer command_buffer = vk_command->singletime_command_begin();

  VkBufferImageCopy region{};
  region.bufferOffset = 0;
  region.bufferRowLength = 0;
  region.bufferImageHeight = 0;
  region.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
  region.imageSubresource.mipLevel = 0;
  region.imageSubresource.baseArrayLayer = 0;
  region.imageSubresource.layerCount = 1;
  region.imageOffset = {0, 0, 0};
  region.imageExtent = {image->width, image->height, 1};
  vkCmdCopyBufferToImage(command_buffer, buffer, image->image, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &region);

  vk_command->singletime_command_end(command_buffer);

  //---------------------------
}
void VK_memory::copy_image_to_buffer(Struct_vk_image* image, VkBuffer buffer){
  //---------------------------

  VkCommandBuffer command_buffer = vk_command->singletime_command_begin();

  VkBufferImageCopy region{};
  region.bufferOffset = 0,
  region.bufferRowLength = 0,
  region.bufferImageHeight = 0,
  region.imageSubresource = {VK_IMAGE_ASPECT_COLOR_BIT, 0, 0, 1},
  region.imageOffset = {0, 0, 0},
  region.imageExtent = {image->width, image->height, 1}; 
  vkCmdCopyImageToBuffer(command_buffer, image->image, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL, buffer, 1, &region);

  vk_command->singletime_command_end(command_buffer);

  //---------------------------
}
