#include "Memory.h"

#include <Vulkan/Namespace.h>


namespace vk::command{

//Constructor / Destructor
Memory::Memory(vk::structure::Vulkan* struct_vulkan){
  //---------------------------

  this->struct_vulkan = struct_vulkan;
  this->vk_command = new vk::command::Command(struct_vulkan);
  this->vk_command_buffer = new vk::command::Command_buffer(struct_vulkan);

  //---------------------------
}
Memory::~Memory(){}

//Image GPU function
void Memory::transfert_texture_to_gpu(vk::structure::Texture* texture){
  //---------------------------

  //Get texture structures
  vk::structure::Image* vk_image = &texture->vk_image;
  utl::media::Image* utl_image = texture->utl_image;
  vk::structure::Buffer* buffer = &texture->stagger;

  //Copy data to stagging buffer
  void* staging_data;
  vkMapMemory(struct_vulkan->device.device, buffer->mem, 0, buffer->size, 0, &staging_data);
  memcpy(staging_data, utl_image->data.data(), buffer->size);
  vkUnmapMemory(struct_vulkan->device.device, buffer->mem);

  //Image transition from undefined layout to read only layout
  vk::structure::Command_buffer* command_buffer = vk_command_buffer->acquire_free_command_buffer();
  vk_command_buffer->start_command_buffer(command_buffer);

  vk_command->image_layout_transition(command_buffer->command, vk_image, TYP_IMAGE_LAYOUT_EMPTY, TYP_IMAGE_LAYOUT_TRANSFER_DST);
  this->copy_buffer_to_image(command_buffer, vk_image, buffer->vbo);
  vk_command->image_layout_transition(command_buffer->command, vk_image, TYP_IMAGE_LAYOUT_TRANSFER_DST, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);

  vk_command_buffer->end_command_buffer(command_buffer);
  vk_command_buffer->submit(command_buffer);

  //---------------------------
}
void Memory::allocate_image_memory(vk::structure::Image* image){
  //---------------------------

  VkMemoryRequirements memRequirements;
  vkGetImageMemoryRequirements(struct_vulkan->device.device, image->image, &memRequirements);

  VkMemoryAllocateInfo allocInfo{};
  allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
  allocInfo.allocationSize = memRequirements.size;
  allocInfo.memoryTypeIndex = find_memory_type(memRequirements.memoryTypeBits, TYP_MEMORY_GPU);
  VkResult result = vkAllocateMemory(struct_vulkan->device.device, &allocInfo, nullptr, &image->mem);
  if(result != VK_SUCCESS){
    throw std::runtime_error("failed to allocate image memory!");
  }

  vkBindImageMemory(struct_vulkan->device.device, image->image, image->mem, 0);

  //---------------------------
}
void Memory::copy_buffer_to_image(vk::structure::Command_buffer* command_buffer, vk::structure::Image* image, VkBuffer buffer){
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
void Memory::copy_image_to_buffer(vk::structure::Command_buffer* command_buffer, vk::structure::Image* image, VkBuffer buffer){
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
void Memory::create_empty_stagger_buffer(vk::structure::Buffer* buffer, VkDeviceSize size){
  if(size == 0) return;
  //---------------------------

  // Create an empty buffer with the specified size
  buffer->size = size;
  this->create_gpu_buffer(buffer->size, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, buffer->vbo);
  this->bind_buffer_memory(TYP_MEMORY_SHARED_CPU_GPU, buffer->vbo, buffer->mem);

  //---------------------------
}
void Memory::create_empty_vertex_buffer(vk::structure::Buffer* buffer, VkDeviceSize size){
  if(size == 0) return;
  //---------------------------

  // Create an empty buffer with the specified size
  buffer->size = size;
  this->create_gpu_buffer(buffer->size, TYP_BUFFER_USAGE_DST_VERTEX, buffer->vbo);
  this->bind_buffer_memory(TYP_MEMORY_GPU, buffer->vbo, buffer->mem);

  //---------------------------
}
void Memory::update_buffer_data(vk::structure::Buffer* buffer, const void* data, VkDeviceSize data_size){
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
void Memory::update_buffer_data(vk::structure::Buffer* buffer, vk::structure::Buffer* stagger, const void* data, VkDeviceSize data_size){
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
  vk_command_buffer->start_command_buffer(command_buffer);

  VkBufferCopy copyRegion = {};
  copyRegion.size = data_size;
  vkCmdCopyBuffer(command_buffer->command, stagger->vbo, buffer->vbo, 1, &copyRegion);

  vk_command_buffer->end_command_buffer(command_buffer);


  //---------------------------
}
void Memory::copy_buffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size){
  //---------------------------
sayHello();
  VkCommandBuffer command_buffer = vk_command->singletime_command_begin();

  VkBufferCopy region{};
  region.size = size;
  vkCmdCopyBuffer(command_buffer, srcBuffer, dstBuffer, 1, &region);

  vk_command->singletime_command_end(command_buffer);

  //---------------------------
}

//Subfunction
void Memory::create_gpu_buffer(VkDeviceSize size, VkBufferUsageFlags usage, VkBuffer& buffer){
  //---------------------------

  VkBufferCreateInfo buffer_info{};
  buffer_info.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
  buffer_info.size = size;
  buffer_info.usage = usage;
  buffer_info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
  VkResult result = vkCreateBuffer(struct_vulkan->device.device, &buffer_info, nullptr, &buffer);

  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to create gpu buffer");
  }

  //---------------------------
}
void Memory::bind_buffer_memory(VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& buffer_memory){
  //---------------------------

  //Get buffer memory requirement
  VkMemoryRequirements memory_requirement;
  vkGetBufferMemoryRequirements(struct_vulkan->device.device, buffer, &memory_requirement);

  //Buffer allocation info
  VkMemoryAllocateInfo allocation_info{};
  allocation_info.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
  allocation_info.allocationSize = memory_requirement.size;
  allocation_info.memoryTypeIndex = find_memory_type(memory_requirement.memoryTypeBits, properties | VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT);

  //Allocate buffer memory on the GPU
  VkResult result = vkAllocateMemory(struct_vulkan->device.device, &allocation_info, nullptr, &buffer_memory);
  if(result != VK_SUCCESS){
    throw std::runtime_error("failed to allocate buffer memory!");
  }

  //Bind the buffer with memory on the GPU side
  vkBindBufferMemory(struct_vulkan->device.device, buffer, buffer_memory, 0);

  //---------------------------
}
uint32_t Memory::find_memory_type(uint32_t typeFilter, VkMemoryPropertyFlags properties){
  //---------------------------

  VkPhysicalDeviceMemoryProperties memProperties;
  vkGetPhysicalDeviceMemoryProperties(struct_vulkan->device.physical_device.physical_device, &memProperties);

  for(uint32_t i=0; i<memProperties.memoryTypeCount; i++){
    if((typeFilter &(1<<i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties){
      return i;
    }
  }

  throw std::runtime_error("failed to find suitable memory type!");

  //---------------------------
}

}
