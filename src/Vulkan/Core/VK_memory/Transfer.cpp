#include "Transfer.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk::memory{

//Constructor / Destructor
Transfer::Transfer(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_transition = new vk::memory::Transition(vk_struct);
  this->vk_command = new vk::commandbuffer::Command_buffer(vk_struct);
  this->vk_command_allocator = new vk::commandbuffer::Allocator(vk_struct);

  //---------------------------
}
Transfer::~Transfer(){}

//Texture function
void Transfer::copy_texture_to_gpu(vk::structure::Texture& texture, void* data, VkImageLayout final_layout){
  //---------------------------

  //Copy data to stagging buffer
  void* staging_data;
  vkMapMemory(vk_struct->core.device.handle, texture.stagger.mem, 0, texture.stagger.size, 0, &staging_data);
  memcpy(staging_data, data, texture.stagger.size);
  vkUnmapMemory(vk_struct->core.device.handle, texture.stagger.mem);

  //Image transition from undefined layout to read only layout
  std::shared_ptr<vk::structure::Command_buffer> command_buffer = vk_command->query_free_command_buffer(vk_struct->core.device.queue.graphics);
  vk_command->start_command_buffer_primary(*command_buffer);

  //Transition + copy
  vk_transition->image_layout_transition(command_buffer->handle, texture.surface, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);
  VkBufferImageCopy region{};
  region.bufferOffset = 0;
  region.bufferRowLength = 0;
  region.bufferImageHeight = texture.surface.height;
  region.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
  region.imageSubresource.mipLevel = 0;
  region.imageSubresource.baseArrayLayer = 0;
  region.imageSubresource.layerCount = 1;
  region.imageOffset = {0, 0, 0};
  region.imageExtent = {texture.surface.width, texture.surface.height, 1};
  vkCmdCopyBufferToImage(command_buffer->handle, texture.stagger.vbo, texture.surface.handle, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &region);
  vk_transition->image_layout_transition(command_buffer->handle, texture.surface, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
  vk_transition->image_layout_transition(command_buffer->handle, texture.surface, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL, final_layout);

  //End and submit command
  vk_command->end_command_buffer(*command_buffer);
  vk_command->submit_command_buffer(command_buffer, vk_struct->core.command.graphics);

  //---------------------------
}
void Transfer::copy_gpu_image_to_buffer(vk::structure::Image& image, VkBuffer buffer){
  //---------------------------

  //Image transition from undefined layout to read only layout
  std::shared_ptr<vk::structure::Command_buffer> command_buffer = vk_command->query_free_command_buffer(vk_struct->core.device.queue.graphics);
  vk_command->start_command_buffer_primary(*command_buffer);

  // Image transition + copy
  vk_transition->image_layout_transition(command_buffer->handle, image, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL);
  VkBufferImageCopy region{};
  region.bufferOffset = 0,
  region.bufferRowLength = 0,
  region.bufferImageHeight = 0,
  region.imageSubresource = {VK_IMAGE_ASPECT_COLOR_BIT, 0, 0, 1},
  region.imageOffset = {0, 0, 0},
  region.imageExtent = {image.width, image.height, 1};
  vkCmdCopyImageToBuffer(command_buffer->handle, image.handle, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL, buffer, 1, &region);
  vk_transition->image_layout_transition(command_buffer->handle, image, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);

  //End and submit command buffer
  vk_command->end_command_buffer(*command_buffer);
  vk_command->submit_command_buffer(command_buffer, vk_struct->core.command.graphics);

  //---------------------------
}
void Transfer::blit_gpu_image_to_gpu_image(vk::structure::Image& image_src, vk::structure::Image& image_dst){
  //---------------------------

  // Image transition from undefined layout to transfer source layout
  std::shared_ptr<vk::structure::Command_buffer> command_buffer = vk_command->query_free_command_buffer(vk_struct->core.device.queue.graphics);
  vk_command->start_command_buffer_primary(*command_buffer);

  // Image transition
  vk_transition->image_layout_transition(command_buffer->handle, image_src, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL);
  vk_transition->image_layout_transition(command_buffer->handle, image_dst, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);

  // Blit image
  VkImageBlit region{};
  region.srcSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT; // or VK_IMAGE_ASPECT_DEPTH_BIT for depth images
  region.srcSubresource.layerCount = 1;
  region.srcOffsets[1].x = image_src.width; // Width of the source image
  region.srcOffsets[1].y = image_src.height; // Height of the source image
  region.srcOffsets[1].z = 1;
  region.dstSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT; // or VK_IMAGE_ASPECT_DEPTH_BIT for depth images
  region.dstSubresource.layerCount = 1;
  region.dstOffsets[1].x = image_dst.width; // Width of the destination image
  region.dstOffsets[1].y = image_dst.height; // Height of the destination image
  region.dstOffsets[1].z = 1;
  vkCmdBlitImage(command_buffer->handle, image_src.handle, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL, image_dst.handle, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &region, VK_FILTER_LINEAR);

  // Transition destination image to shader read-only optimal layout if needed
  // vk_transition->imageLayoutTransition(commandBuffer.get(), dstImage, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);

  //End and submit command buffer
  vk_command->end_command_buffer(*command_buffer);
  vk_command->submit_command_buffer(command_buffer, vk_struct->core.command.graphics);

  //---------------------------
}
void Transfer::copy_gpu_image_to_gpu_image_standalone(vk::structure::Image& image_src, vk::structure::Image& image_dst){
  //---------------------------

  // Image transition from undefined layout to transfer source layout
  std::shared_ptr<vk::structure::Command_buffer> command_buffer = vk_command->query_free_command_buffer(vk_struct->core.device.queue.graphics);
  vk_command->start_command_buffer_primary(*command_buffer);

  // Image transition
  vk_transition->image_layout_transition(command_buffer->handle, image_src, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL);
  vk_transition->image_layout_transition(command_buffer->handle, image_dst, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);

  // Copy image
  VkImageCopy region{};
  region.srcSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT; // or VK_IMAGE_ASPECT_DEPTH_BIT for depth images
  region.srcSubresource.layerCount = 1;
  region.dstSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT; // or VK_IMAGE_ASPECT_DEPTH_BIT for depth images
  region.dstSubresource.layerCount = 1;
  region.extent.width = image_src.width; // Width of the source image
  region.extent.height = image_src.height; // Height of the source image
  region.extent.depth = 1;
  vkCmdCopyImage(command_buffer->handle, image_src.handle, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL, image_dst.handle, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &region);

  // Transition destination image to shader read-only optimal layout if needed
  // vk_transition->imageLayoutTransition(commandBuffer.get(), dstImage, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);

  //End and submit command buffer
  vk_command->end_command_buffer(*command_buffer);
  vk_command->submit_command_buffer(command_buffer, vk_struct->core.command.graphics);

  //---------------------------
}
std::shared_ptr<vk::structure::Command_buffer> Transfer::copy_gpu_image_to_gpu_image(vk::structure::Image& image_src, vk::structure::Image& image_dst){
  //---------------------------

  // Image transition from undefined layout to transfer source layout
  std::shared_ptr<vk::structure::Command_buffer> command_buffer = vk_command->query_free_command_buffer(vk_struct->core.device.queue.graphics);
  vk_command->start_command_buffer_primary(*command_buffer);

  // Image transition
  vk_transition->image_layout_transition(command_buffer->handle, image_src, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL);
  vk_transition->image_layout_transition(command_buffer->handle, image_dst, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);

  // Copy image
  VkImageCopy region{};
  region.srcSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT; // or VK_IMAGE_ASPECT_DEPTH_BIT for depth images
  region.srcSubresource.layerCount = 1;
  region.dstSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT; // or VK_IMAGE_ASPECT_DEPTH_BIT for depth images
  region.dstSubresource.layerCount = 1;
  region.extent.width = image_src.width; // Width of the source image
  region.extent.height = image_src.height; // Height of the source image
  region.extent.depth = 1;
  vkCmdCopyImage(command_buffer->handle, image_src.handle, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL, image_dst.handle, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &region);

  // Transition destination image to shader read-only optimal layout if needed
  vk_transition->image_layout_transition(command_buffer->handle, image_dst, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_PRESENT_SRC_KHR);

  //End and submit command buffer
  vk_command->end_command_buffer(*command_buffer);

  //---------------------------
  return command_buffer;
}

//Vertex function
void Transfer::copy_vertex_to_gpu(vk::structure::Buffer& buffer, const void* data, VkDeviceSize data_size){
  if(data_size == 0) return;
  //---------------------------

  // Map the buffer's memory and copy the data
  void* mappedMemory;
  VkResult result = vkMapMemory(vk_struct->core.device.handle, buffer.mem, 0, data_size, 0, &mappedMemory);
  if(result != VK_SUCCESS){
    throw std::runtime_error("Failed to map buffer memory!");
  }
  memcpy(mappedMemory, data, static_cast<size_t>(data_size));
  vkUnmapMemory(vk_struct->core.device.handle, buffer.mem);

  //---------------------------
}
void Transfer::copy_vertex_to_gpu(vk::structure::Buffer& buffer, vk::structure::Buffer& stagger, const void* data, VkDeviceSize data_size){
  if(data_size == 0) return;
  //---------------------------

  // Map the buffer's memory and copy the data
  void* mappedMemory;
  VkResult result = vkMapMemory(vk_struct->core.device.handle, stagger.mem, 0, data_size, 0, &mappedMemory);
  if(result != VK_SUCCESS){
    throw std::runtime_error("Failed to map buffer memory!");
  }
  memcpy(mappedMemory, data, static_cast<size_t>(data_size));
  vkUnmapMemory(vk_struct->core.device.handle, stagger.mem);

  // Create command buffer to cpy on gpu
  std::shared_ptr<vk::structure::Command_buffer> command_buffer = vk_command->query_free_command_buffer(vk_struct->core.device.queue.transfer);
  command_buffer->name = "transfer::data";
  if(command_buffer == nullptr) return;

  vk_command->start_command_buffer_primary(*command_buffer);

  VkBufferCopy region = {};
  region.size = data_size;
  vkCmdCopyBuffer(command_buffer->handle, stagger.vbo, buffer.vbo, 1, &region);

  vk_command->end_command_buffer(*command_buffer);
  vk_command->submit_command_buffer(command_buffer, vk_struct->core.command.transfer);

  //---------------------------
}

}
