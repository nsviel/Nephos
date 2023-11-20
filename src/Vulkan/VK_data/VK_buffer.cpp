#include "VK_buffer.h"

#include <VK_main/Struct_vulkan.h>
#include <VK_command/VK_command.h>


//Constructor / Destructor
VK_buffer::VK_buffer(Struct_vulkan* struct_vulkan){
  //---------------------------

  this->struct_vulkan = struct_vulkan;
  this->vk_command = new VK_command(struct_vulkan);

  //---------------------------
}
VK_buffer::~VK_buffer(){}

//Main function
void VK_buffer::create_buffers(Struct_vk_entity* data){
  //---------------------------

  this->create_buffer(&data->xyz, data->object->xyz);
  this->create_buffer(&data->rgb, data->object->rgb);
  this->create_buffer(&data->uv, data->object->uv);

  //---------------------------
}
void VK_buffer::clean_buffers(Struct_vk_entity* data){
  //---------------------------

  this->clean_buffer(&data->xyz);
  this->clean_buffer(&data->rgb);
  this->clean_buffer(&data->uv);

  //---------------------------
}

//Data buffer functions
template <typename VertexType> void VK_buffer::create_buffer(Struct_vk_buffer* buffer, vector<VertexType>& vertices){
  //---------------------------

  if(vertices.size() == 0){return;}

  VkBuffer staging_buffer;
  VkDeviceMemory staging_buffer_memory;
  VkDeviceSize size = sizeof(vertices[0]) * vertices.size();

  // Initialize staging buffer
  this->create_gpu_buffer(size, TYP_BUFFER_USAGE_SRC, staging_buffer);
  this->bind_buffer_memory(TYP_MEMORY_SHARED_CPU_GPU, staging_buffer, staging_buffer_memory);

  // Copy the vertex data from the CPU to the GPU
  void* data_map;
  vkMapMemory(struct_vulkan->device.device, staging_buffer_memory, 0, size, 0, &data_map);
  memcpy(data_map, vertices.data(), static_cast<size_t>(size));
  vkUnmapMemory(struct_vulkan->device.device, staging_buffer_memory);

  // Initialize destination buffer
  this->create_gpu_buffer(size, TYP_BUFFER_USAGE_DST_VERTEX, buffer->vbo);
  this->bind_buffer_memory(TYP_MEMORY_GPU, buffer->vbo, buffer->mem);
  this->copy_buffer_to_gpu(staging_buffer, buffer->vbo, size);

  // Cleanup staging buffer resources
  vkDestroyBuffer(struct_vulkan->device.device, staging_buffer, nullptr);
  vkFreeMemory(struct_vulkan->device.device, staging_buffer_memory, nullptr);

  //---------------------------
}
void VK_buffer::clean_buffer(Struct_vk_buffer* buffer){
  //---------------------------

  if(buffer->vbo != VK_NULL_HANDLE){
    vkDestroyBuffer(struct_vulkan->device.device, buffer->vbo, nullptr);
  }

  if(buffer->mem != VK_NULL_HANDLE){
    vkFreeMemory(struct_vulkan->device.device, buffer->mem, nullptr);
  }

  //---------------------------
}

//Buffer functions
void VK_buffer::create_gpu_buffer(VkDeviceSize size, VkBufferUsageFlags usage, VkBuffer& buffer){
  //---------------------------

  VkBufferCreateInfo bufferInfo{};
  bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
  bufferInfo.size = size;
  bufferInfo.usage = usage;
  bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

  VkResult result = vkCreateBuffer(struct_vulkan->device.device, &bufferInfo, nullptr, &buffer);

  if(result != VK_SUCCESS){
    throw std::runtime_error("failed to create buffer!");
  }

  //---------------------------
}
void VK_buffer::bind_buffer_memory(VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& buffer_memory){
  //---------------------------

  //Get buffer memory requirement
  VkMemoryRequirements buffer_mem_requirement;
  vkGetBufferMemoryRequirements(struct_vulkan->device.device, buffer, &buffer_mem_requirement);

  //Buffer allocation info
  VkMemoryAllocateInfo buffer_allocation_info{};
  buffer_allocation_info.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
  buffer_allocation_info.allocationSize = buffer_mem_requirement.size;
  buffer_allocation_info.memoryTypeIndex = find_memory_type(buffer_mem_requirement.memoryTypeBits, properties);

  //Allocate buffer memory on the GPU
  VkResult result = vkAllocateMemory(struct_vulkan->device.device, &buffer_allocation_info, nullptr, &buffer_memory);
  if(result != VK_SUCCESS){
    throw std::runtime_error("failed to allocate buffer memory!");
  }

  //Bind the buffer with memory on the GPU side
  vkBindBufferMemory(struct_vulkan->device.device, buffer, buffer_memory, 0);

  //---------------------------
}
void VK_buffer::copy_buffer_to_gpu(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size){
  //---------------------------

  VkCommandBuffer command_buffer = vk_command->singletime_command_begin();

  VkBufferCopy copyRegion{};
  copyRegion.size = size;
  vkCmdCopyBuffer(command_buffer, srcBuffer, dstBuffer, 1, &copyRegion);

  vk_command->singletime_command_end(command_buffer);

  //---------------------------
}
uint32_t VK_buffer::find_memory_type(uint32_t typeFilter, VkMemoryPropertyFlags properties){
  //---------------------------

  VkPhysicalDeviceMemoryProperties memProperties;
  vkGetPhysicalDeviceMemoryProperties(struct_vulkan->device.struct_device.physical_device, &memProperties);

  for(uint32_t i=0; i<memProperties.memoryTypeCount; i++){
    if((typeFilter &(1<<i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties){
      return i;
    }
  }

  throw std::runtime_error("failed to find suitable memory type!");

  //---------------------------
}
