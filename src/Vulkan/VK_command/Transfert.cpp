#include "Transfert.h"

#include <Vulkan/Namespace.h>


namespace vk::command{

//Constructor / Destructor
Transfert::Transfert(vk::structure::Vulkan* struct_vulkan){
  //---------------------------

  this->struct_vulkan = struct_vulkan;
  this->vk_image = new vk::image::Image(struct_vulkan);
  this->vk_command_buffer = new vk::command::Command_buffer(struct_vulkan);

  //---------------------------
}
Transfert::~Transfert(){}

//Image GPU function
void Transfert::copy_texture_to_gpu(vk::structure::Texture* texture){
  //---------------------------

  //Get texture structures
  vk::structure::Image* image = &texture->vk_image;
  utl::media::Image* utl_image = texture->utl_image;
  vk::structure::Buffer* buffer = &texture->stagger;

  //Copy data to stagging buffer
  void* staging_data;
  vkMapMemory(struct_vulkan->device.device, buffer->mem, 0, buffer->size, 0, &staging_data);
  memcpy(staging_data, utl_image->data.data(), buffer->size);
  vkUnmapMemory(struct_vulkan->device.device, buffer->mem);

  //Image transition from undefined layout to read only layout
  vk::structure::Command_buffer* command_buffer = vk_command_buffer->acquire_free_command_buffer();
  vk_command_buffer->start_command_buffer_primary(command_buffer);

  vk_image->image_layout_transition(command_buffer->command, image, TYP_IMAGE_LAYOUT_EMPTY, TYP_IMAGE_LAYOUT_TRANSFER_DST);
  this->copy_buffer_to_image(command_buffer, image, buffer->vbo);
  vk_image->image_layout_transition(command_buffer->command, image, TYP_IMAGE_LAYOUT_TRANSFER_DST, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);

  vk_command_buffer->end_command_buffer(command_buffer);
  vk_command_buffer->submit(command_buffer);

  //---------------------------
}
void Transfert::copy_buffer_to_image(vk::structure::Command_buffer* command_buffer, vk::structure::Image* image, VkBuffer buffer){
  //---------------------------

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
  vkCmdCopyBufferToImage(command_buffer->command, buffer, image->image, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &region);

  //---------------------------
}
void Transfert::copy_image_to_buffer(vk::structure::Command_buffer* command_buffer, vk::structure::Image* image, VkBuffer buffer){
  //---------------------------

  VkBufferImageCopy region{};
  region.bufferOffset = 0,
  region.bufferRowLength = 0,
  region.bufferImageHeight = 0,
  region.imageSubresource = {VK_IMAGE_ASPECT_COLOR_BIT, 0, 0, 1},
  region.imageOffset = {0, 0, 0},
  region.imageExtent = {image->width, image->height, 1};
  vkCmdCopyImageToBuffer(command_buffer->command, image->image, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL, buffer, 1, &region);

  //---------------------------
}

//Buffer GPU function
void Transfert::copy_data_to_gpu(vk::structure::Buffer* buffer, const void* data, VkDeviceSize data_size){
  //---------------------------

  if (data_size == 0) {
    throw std::runtime_error("Data size is zero!");
  }

  // Map the buffer's memory and copy the data
  void* mappedMemory;
  VkResult result = vkMapMemory(struct_vulkan->device.device, buffer->mem, 0, data_size, 0, &mappedMemory);
  if (result != VK_SUCCESS) {
    throw std::runtime_error("Failed to map buffer memory!");
  }
  memcpy(mappedMemory, data, static_cast<size_t>(data_size));
  vkUnmapMemory(struct_vulkan->device.device, buffer->mem);

  //---------------------------
}
void Transfert::copy_data_to_gpu(vk::structure::Buffer* buffer, vk::structure::Buffer* stagger, const void* data, VkDeviceSize data_size){
  //---------------------------

  if (data_size == 0) {
    throw std::runtime_error("Data size is zero!");
  }

  // Map the buffer's memory and copy the data
  void* mappedMemory;
  VkResult result = vkMapMemory(struct_vulkan->device.device, stagger->mem, 0, data_size, 0, &mappedMemory);
  if (result != VK_SUCCESS) {
    throw std::runtime_error("Failed to map buffer memory!");
  }
  memcpy(mappedMemory, data, static_cast<size_t>(data_size));
  vkUnmapMemory(struct_vulkan->device.device, stagger->mem);



  // Create command buffer to cpy on gpu
  vk::structure::Command_buffer* command_buffer = vk_command_buffer->acquire_free_command_buffer();
  vk_command_buffer->start_command_buffer_primary(command_buffer);

  VkBufferCopy copyRegion = {};
  copyRegion.size = data_size;
  vkCmdCopyBuffer(command_buffer->command, stagger->vbo, buffer->vbo, 1, &copyRegion);

  vk_command_buffer->end_command_buffer(command_buffer);


  //---------------------------
}

}
