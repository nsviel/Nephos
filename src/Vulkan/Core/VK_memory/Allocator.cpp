#include "Allocator.h"

#include <Vulkan/Namespace.h>


namespace vk::memory{

//Constructor / Destructor
Allocator::Allocator(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;

  //---------------------------
}
Allocator::~Allocator(){}

//Image GPU function
void Allocator::allocate_image_memory(vk::structure::Image& image){
  //---------------------------

  VkMemoryRequirements memRequirements;
  vkGetImageMemoryRequirements(vk_struct->device.handle, image.handle, &memRequirements);

  VkMemoryAllocateInfo allocInfo{};
  allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
  allocInfo.allocationSize = memRequirements.size;
  allocInfo.memoryTypeIndex = find_memory_type(memRequirements.memoryTypeBits, TYP_MEMORY_GPU);
  VkResult result = vkAllocateMemory(vk_struct->device.handle, &allocInfo, nullptr, &image.mem);
  if(result != VK_SUCCESS){
    throw std::runtime_error("failed to allocate image memory!");
  }

  vkBindImageMemory(vk_struct->device.handle, image.handle, image.mem, 0);

  //---------------------------
}

//Buffer GPU function
void Allocator::allocate_empty_stagger_buffer(vk::data::structure::Buffer& buffer, VkDeviceSize size){
  if(size == 0) return;
  //---------------------------

  // Create an empty buffer with the specified size
  buffer.size = size;
  this->create_gpu_buffer(buffer.size, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, buffer.vbo);
  this->bind_buffer_memory(TYP_MEMORY_SHARED_CPU_GPU, buffer.vbo, buffer.mem);

  //---------------------------
}
void Allocator::allocate_empty_vertex_buffer(vk::data::structure::Buffer& buffer, VkDeviceSize size){
  if(size == 0) return;
  //---------------------------

  // Create an empty buffer with the specified size
  buffer.size = size;
  this->create_gpu_buffer(buffer.size, TYP_BUFFER_USAGE_DST_VERTEX, buffer.vbo);
  this->bind_buffer_memory(TYP_MEMORY_GPU, buffer.vbo, buffer.mem);

  //---------------------------
}

//Subfunction
void Allocator::create_gpu_buffer(VkDeviceSize size, VkBufferUsageFlags usage, VkBuffer& buffer){
  //---------------------------

  VkBufferCreateInfo buffer_info{};
  buffer_info.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
  buffer_info.size = size;
  buffer_info.usage = usage;
  buffer_info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
  VkResult result = vkCreateBuffer(vk_struct->device.handle, &buffer_info, nullptr, &buffer);

  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to create gpu buffer");
  }

  //---------------------------
}
void Allocator::bind_buffer_memory(VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& buffer_memory){
  //---------------------------

  //Get buffer memory requirement
  VkMemoryRequirements memory_requirement;
  vkGetBufferMemoryRequirements(vk_struct->device.handle, buffer, &memory_requirement);

  //Buffer allocation info
  VkMemoryAllocateInfo allocation_info{};
  allocation_info.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
  allocation_info.allocationSize = memory_requirement.size;
  allocation_info.memoryTypeIndex = find_memory_type(memory_requirement.memoryTypeBits, properties | VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT);

  //Allocate buffer memory on the GPU
  VkResult result = vkAllocateMemory(vk_struct->device.handle, &allocation_info, nullptr, &buffer_memory);
  if(result != VK_SUCCESS){
    throw std::runtime_error("failed to allocate buffer memory!");
  }

  //Bind the buffer with memory on the GPU side
  vkBindBufferMemory(vk_struct->device.handle, buffer, buffer_memory, 0);

  //---------------------------
}
uint32_t Allocator::find_memory_type(uint32_t typeFilter, VkMemoryPropertyFlags properties){
  //---------------------------

  VkPhysicalDeviceMemoryProperties memProperties;
  vkGetPhysicalDeviceMemoryProperties(vk_struct->device.physical_device.handle, &memProperties);

  for(uint32_t i=0; i<memProperties.memoryTypeCount; i++){
    if((typeFilter &(1<<i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties){
      return i;
    }
  }

  throw std::runtime_error("failed to find suitable memory type!");

  //---------------------------
}

}
