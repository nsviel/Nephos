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
  vk_command_buffer->start_command_buffer_primary(command_buffer);

  //Transition + copy
  vk_transition->image_layout_transition(command_buffer->handle, image, TYP_IMAGE_LAYOUT_EMPTY, TYP_IMAGE_LAYOUT_TRANSFER_DST);
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
  vkCmdCopyBufferToImage(command_buffer->handle, buffer, image->handle, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &region);
  vk_transition->image_layout_transition(command_buffer->handle, image, TYP_IMAGE_LAYOUT_TRANSFER_DST, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);

  //End and submit command
  vk_command_buffer->end_command_buffer(command_buffer);
  vk::structure::Command* command = new vk::structure::Command();
  command->command_buffer = command_buffer;
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
  vk_transition->image_layout_transition(command_buffer->handle, image, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL);
  VkBufferImageCopy region{};
  region.bufferOffset = 0,
  region.bufferRowLength = 0,
  region.bufferImageHeight = 0,
  region.imageSubresource = {VK_IMAGE_ASPECT_COLOR_BIT, 0, 0, 1},
  region.imageOffset = {0, 0, 0},
  region.imageExtent = {image->width, image->height, 1};
  vkCmdCopyImageToBuffer(command_buffer->handle, image->handle, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL, buffer, 1, &region);
  vk_transition->image_layout_transition(command_buffer->handle, image, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);

  //End and submit command buffer
  vk_command_buffer->end_command_buffer(command_buffer);
  vk::structure::Command* command = new vk::structure::Command();
  command->command_buffer = command_buffer;
  vk_struct->queue.graphics->add_command(command);

  //---------------------------
}
void Transfer::copy_image_to_image_standalone(vk::structure::Image* image_src, vk::structure::Image* image_dst){
  //---------------------------

  // Image transition from undefined layout to transfer source layout
  vk::pool::Command_buffer* pool = vk_command_allocator->query_free_pool(&vk_struct->device.queue.graphics);
  vk::structure::Command_buffer* command_buffer = vk_command_buffer->query_free_command_buffer(pool);
  vk_command_buffer->start_command_buffer_primary(command_buffer);

  // Image transition
  vk_transition->image_layout_transition(command_buffer->handle, image_src, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL);
  vk_transition->image_layout_transition(command_buffer->handle, image_dst, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);

  // Copy image
  VkImageCopy region{};
  region.srcSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT; // or VK_IMAGE_ASPECT_DEPTH_BIT for depth images
  region.srcSubresource.layerCount = 1;
  region.dstSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT; // or VK_IMAGE_ASPECT_DEPTH_BIT for depth images
  region.dstSubresource.layerCount = 1;
  region.extent.width = image_src->width; // Width of the source image
  region.extent.height = image_src->height; // Height of the source image
  region.extent.depth = 1;
  vkCmdCopyImage(command_buffer->handle, image_src->handle, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL, image_dst->handle, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &region);

  // Transition destination image to shader read-only optimal layout if needed
  // vk_transition->imageLayoutTransition(commandBuffer.get(), dstImage, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);

  //End and submit command buffer
  vk_command_buffer->end_command_buffer(command_buffer);
  vk::structure::Command* command = new vk::structure::Command();
  command->command_buffer = command_buffer;
  vk_struct->queue.graphics->add_command(command);

  //---------------------------
}
void Transfer::blit_image_to_image(vk::structure::Image* image_src, vk::structure::Image* image_dst){
  //---------------------------

  // Image transition from undefined layout to transfer source layout
  vk::pool::Command_buffer* pool = vk_command_allocator->query_free_pool(&vk_struct->device.queue.graphics);
  vk::structure::Command_buffer* command_buffer = vk_command_buffer->query_free_command_buffer(pool);
  vk_command_buffer->start_command_buffer_primary(command_buffer);

  // Image transition
  vk_transition->image_layout_transition(command_buffer->handle, image_src, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL);
  vk_transition->image_layout_transition(command_buffer->handle, image_dst, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);

  // Blit image
  VkImageBlit region{};
  region.srcSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT; // or VK_IMAGE_ASPECT_DEPTH_BIT for depth images
  region.srcSubresource.layerCount = 1;
  region.srcOffsets[1].x = image_src->width; // Width of the source image
  region.srcOffsets[1].y = image_src->height; // Height of the source image
  region.srcOffsets[1].z = 1;
  region.dstSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT; // or VK_IMAGE_ASPECT_DEPTH_BIT for depth images
  region.dstSubresource.layerCount = 1;
  region.dstOffsets[1].x = image_dst->width; // Width of the destination image
  region.dstOffsets[1].y = image_dst->height; // Height of the destination image
  region.dstOffsets[1].z = 1;
  vkCmdBlitImage(command_buffer->handle, image_src->handle, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL, image_dst->handle, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &region, VK_FILTER_LINEAR);

  // Transition destination image to shader read-only optimal layout if needed
  // vk_transition->imageLayoutTransition(commandBuffer.get(), dstImage, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);

  //End and submit command buffer
  vk_command_buffer->end_command_buffer(command_buffer);
  vk::structure::Command* command = new vk::structure::Command();
  command->command_buffer = command_buffer;
  vk_struct->queue.graphics->add_command(command);

  //---------------------------
}
vk::structure::Command_buffer* Transfer::copy_image_to_image(vk::structure::Image* image_src, vk::structure::Image* image_dst){
  //---------------------------

  // Image transition from undefined layout to transfer source layout
  vk::pool::Command_buffer* pool = vk_command_allocator->query_free_pool(&vk_struct->device.queue.graphics);
  vk::structure::Command_buffer* command_buffer = vk_command_buffer->query_free_command_buffer(pool);
  vk_command_buffer->start_command_buffer_primary(command_buffer);

  // Image transition
  vk_transition->image_layout_transition(command_buffer->handle, image_src, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL);
  vk_transition->image_layout_transition(command_buffer->handle, image_dst, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);

  // Copy image
  VkImageCopy region{};
  region.srcSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT; // or VK_IMAGE_ASPECT_DEPTH_BIT for depth images
  region.srcSubresource.layerCount = 1;
  region.dstSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT; // or VK_IMAGE_ASPECT_DEPTH_BIT for depth images
  region.dstSubresource.layerCount = 1;
  region.extent.width = image_src->width; // Width of the source image
  region.extent.height = image_src->height; // Height of the source image
  region.extent.depth = 1;
  vkCmdCopyImage(command_buffer->handle, image_src->handle, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL, image_dst->handle, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &region);

  // Transition destination image to shader read-only optimal layout if needed
  vk_transition->image_layout_transition(command_buffer->handle, image_dst->handle, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_PRESENT_SRC_KHR);

  //End and submit command buffer
  vk_command_buffer->end_command_buffer(command_buffer);

  //---------------------------
  return command_buffer;
}

//Buffer GPU function
void Transfer::copy_data_to_gpu(vk::structure::Buffer* buffer, const void* data, VkDeviceSize data_size){
  if(data_size == 0) return;
  //---------------------------

  // Map the buffer's memory and copy the data
  void* mappedMemory;
  VkResult result = vkMapMemory(vk_struct->device.handle, buffer->mem, 0, data_size, 0, &mappedMemory);
  if(result != VK_SUCCESS){
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
  if(result != VK_SUCCESS){
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

  VkBufferCopy region = {};
  region.size = data_size;
  vkCmdCopyBuffer(command_buffer->handle, stagger->vbo, buffer->vbo, 1, &region);

  vk_command_buffer->end_command_buffer(command_buffer);
  vk_struct->queue.transfer->add_command(command_buffer);

  //---------------------------
}

}
