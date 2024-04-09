#include "Transfer.h"

#include <Vulkan/Namespace.h>


namespace vk::memory{

//Constructor / Destructor
Transfer::Transfer(vk::structure::Vulkan* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_transition = new vk::image::Transition(vk_struct);
  this->vk_command_buffer = new vk::command::Command_buffer(vk_struct);
  this->vk_command_allocator = new vk::command::Allocator(vk_struct);

  //---------------------------
}
Transfer::~Transfer(){}

//Image GPU function
void Transfer::copy_texture_to_gpu(vk::structure::Texture* texture){
  //---------------------------

  //Get texture structures
  vk::structure::Image* image = &texture->vk_image;
  utl::media::Image* utl_image = texture->utl_image;
  vk::structure::Buffer* buffer = &texture->stagger;

  //Copy data to stagging buffer
  void* staging_data;
  vkMapMemory(vk_struct->device.handle, buffer->mem, 0, buffer->size, 0, &staging_data);
  memcpy(staging_data, utl_image->data.data(), buffer->size);
  vkUnmapMemory(vk_struct->device.handle, buffer->mem);

  this->copy_buffer_to_image(image, buffer->vbo);

  //---------------------------
}
void Transfer::copy_buffer_to_image(vk::structure::Image* image, VkBuffer buffer){
  //---------------------------

  //Image transition from undefined layout to read only layout
  vk::pool::Command_buffer* pool = vk_command_allocator->query_free_pool(&vk_struct->device.queue.graphics);
  vk::structure::Command_buffer* command_buffer = vk_command_buffer->query_free_command_buffer(pool);
  command_buffer->name = "transfer::texture";
  vk_command_buffer->start_command_buffer_primary(command_buffer);

  //Transition + copy
  vk_transition->image_layout_transition(command_buffer->command, image, TYP_IMAGE_LAYOUT_EMPTY, TYP_IMAGE_LAYOUT_TRANSFER_DST);
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
  vk_transition->image_layout_transition(command_buffer->command, image, TYP_IMAGE_LAYOUT_TRANSFER_DST, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);

  //End and submit command
  vk_command_buffer->end_command_buffer(command_buffer);
  vk::structure::Command* command = new vk::structure::Command();
  command->vec_command_buffer.push_back(command_buffer);
  vk_struct->queue.graphics->add_command(command);

  //---------------------------
}
void Transfer::copy_image_to_buffer(vk::structure::Image* image, VkBuffer buffer){
  //---------------------------

  //Image transition from undefined layout to read only layout
  vk::pool::Command_buffer* pool = vk_command_allocator->query_free_pool(&vk_struct->device.queue.graphics);
  vk::structure::Command_buffer* command_buffer = vk_command_buffer->query_free_command_buffer(pool);
  vk_command_buffer->start_command_buffer_primary(command_buffer);

  // Image transition + copy
  vk_transition->image_layout_transition(command_buffer->command, image, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL);
  VkBufferImageCopy region{};
  region.bufferOffset = 0,
  region.bufferRowLength = 0,
  region.bufferImageHeight = 0,
  region.imageSubresource = {VK_IMAGE_ASPECT_COLOR_BIT, 0, 0, 1},
  region.imageOffset = {0, 0, 0},
  region.imageExtent = {image->width, image->height, 1};
  vkCmdCopyImageToBuffer(command_buffer->command, image->image, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL, buffer, 1, &region);
  vk_transition->image_layout_transition(command_buffer->command, image, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);

  //End and submit command buffer
  vk_command_buffer->end_command_buffer(command_buffer);
  vk::structure::Command* command = new vk::structure::Command();
  command->vec_command_buffer.push_back(command_buffer);
  vk_struct->queue.graphics->add_command(command);

  //---------------------------
}

//Buffer GPU function
void Transfer::copy_data_to_gpu(vk::structure::Buffer* buffer, const void* data, VkDeviceSize data_size){
  if(data_size == 0) return;
  //---------------------------

  // Map the buffer's memory and copy the data
  void* mappedMemory;
  VkResult result = vkMapMemory(vk_struct->device.handle, buffer->mem, 0, data_size, 0, &mappedMemory);
  if (result != VK_SUCCESS) {
    throw std::runtime_error("Failed to map buffer memory!");
  }
  memcpy(mappedMemory, data, static_cast<size_t>(data_size));
  vkUnmapMemory(vk_struct->device.handle, buffer->mem);

  //---------------------------
}
void Transfer::copy_data_to_gpu(vk::structure::Buffer* buffer, vk::structure::Buffer* stagger, const void* data, VkDeviceSize data_size){
  if(data_size == 0) return;
  //---------------------------

  // Map the buffer's memory and copy the data
  void* mappedMemory;
  VkResult result = vkMapMemory(vk_struct->device.handle, stagger->mem, 0, data_size, 0, &mappedMemory);
  if (result != VK_SUCCESS) {
    throw std::runtime_error("Failed to map buffer memory!");
  }
  memcpy(mappedMemory, data, static_cast<size_t>(data_size));
  vkUnmapMemory(vk_struct->device.handle, stagger->mem);

  // Create command buffer to cpy on gpu
  vk::pool::Command_buffer* pool = vk_command_allocator->query_free_pool(&vk_struct->device.queue.transfer);
  vk::structure::Command_buffer* command_buffer = vk_command_buffer->query_free_command_buffer(pool);
  command_buffer->name = "transfer::data";
  if(command_buffer == nullptr) return;

  vk_command_buffer->start_command_buffer_primary(command_buffer);

  VkBufferCopy copyRegion = {};
  copyRegion.size = data_size;
  vkCmdCopyBuffer(command_buffer->command, stagger->vbo, buffer->vbo, 1, &copyRegion);

  vk_command_buffer->end_command_buffer(command_buffer);
  vk_struct->queue.transfer->add_command(command_buffer);

  //---------------------------
}

}
