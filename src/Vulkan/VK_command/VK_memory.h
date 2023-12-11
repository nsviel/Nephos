#pragma once

#include <VK_struct/Namespace.h>
#include <UTL_specific/common.h>


class VK_command;


class VK_memory
{
public:
  //Constructor / Destructor
  VK_memory(vk::structure::Struct_vulkan* struct_vulkan);
  ~VK_memory();

public:
  //Image GPU function
  void transfert_image_to_gpu(vk::structure::Image* image);
  void allocate_image_memory(vk::structure::Image* image);
  void copy_buffer_to_image(vk::structure::Image* image, VkBuffer buffer);
  void copy_image_to_buffer(vk::structure::Image* image, VkBuffer buffer);

  //Buffer GPU function
  void transfert_buffer_to_gpu(vk::structure::Buffer* buffer, vector<vec2>& vertices);
  void transfert_buffer_to_gpu(vk::structure::Buffer* buffer, vector<vec3>& vertices);
  void transfert_buffer_to_gpu(vk::structure::Buffer* buffer, vector<vec4>& vertices);
  void copy_buffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);

  //Subfunction
  void bind_buffer_memory(VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
  void create_gpu_buffer(VkDeviceSize size, VkBufferUsageFlags usage, VkBuffer& buffer);
  uint32_t find_memory_type(uint32_t typeFilter, VkMemoryPropertyFlags properties);

private:
  vk::structure::Struct_vulkan* struct_vulkan;
  VK_command* vk_command;
};
