#include "VK_memory.h"

#include <VK_main/Struct_vulkan.h>
#include <VK_command/VK_command.h>


//Constructor / Destructor
VK_memory::VK_memory(Struct_vulkan* struct_vulkan){
  //---------------------------

  this->struct_vulkan = struct_vulkan;
  this->vk_command = new VK_command(struct_vulkan);

  //---------------------------
}
VK_memory::~VK_memory(){}

//Image GPU function
void VK_memory::transfert_image_to_gpu(Struct_vk_image* image){
  //---------------------------

  //Create stagging buffer
  VkBuffer staging_buffer;
  VkDeviceMemory staging_mem;
  VkDeviceSize tex_size = image->width * image->height * 4;
  this->create_gpu_buffer(tex_size, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, staging_buffer);
  this->bind_buffer_memory(TYP_MEMORY_SHARED_CPU_GPU, staging_buffer, staging_mem);

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

//Buffer GPU function
template <typename VertexType>
void VK_memory::transfert_buffer_to_gpu_(Struct_vk_buffer* buffer, vector<VertexType>& vertices){
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
  this->copy_buffer(staging_buffer, buffer->vbo, size);

  // Cleanup staging buffer resources
  vkDestroyBuffer(struct_vulkan->device.device, staging_buffer, nullptr);
  vkFreeMemory(struct_vulkan->device.device, staging_buffer_memory, nullptr);

  //---------------------------
}
void VK_memory::copy_buffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size){
  //---------------------------

  VkCommandBuffer command_buffer = vk_command->singletime_command_begin();

  VkBufferCopy region{};
  region.size = size;
  vkCmdCopyBuffer(command_buffer, srcBuffer, dstBuffer, 1, &region);

  vk_command->singletime_command_end(command_buffer);

  //---------------------------
}

//Subfunction
void VK_memory::create_gpu_buffer(VkDeviceSize size, VkBufferUsageFlags usage, VkBuffer& buffer){
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
void VK_memory::bind_buffer_memory(VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& buffer_memory){
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
uint32_t VK_memory::find_memory_type(uint32_t typeFilter, VkMemoryPropertyFlags properties){
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
