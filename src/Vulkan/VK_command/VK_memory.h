#pragma once

#include <Vulkan/VK_struct/Namespace.h>
#include <Utility/Specific/common.h>


class VK_command;


class VK_memory
{
public:
  //Constructor / Destructor
  VK_memory(vk::structure::Vulkan* struct_vulkan);
  ~VK_memory();

public:
  //Image GPU function
  void transfert_image_to_gpu(vk::structure::Image* image);
  void allocate_image_memory(vk::structure::Image* image);
  void copy_buffer_to_image(vk::structure::Image* image, VkBuffer buffer);
  void copy_image_to_buffer(vk::structure::Image* image, VkBuffer buffer);

  //Buffer GPU function
  void transfert_buffer_to_gpu(vector<vec2>& vertices, vk::structure::Buffer* buffer);
  void transfert_buffer_to_gpu(vector<vec3>& vertices, vk::structure::Buffer* buffer);
  void transfert_buffer_to_gpu(vector<vec4>& vertices, vk::structure::Buffer* buffer);
  void copy_buffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);

  //Subfunction
  void bind_buffer_memory(VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
  void create_gpu_buffer(VkDeviceSize size, VkBufferUsageFlags usage, VkBuffer& buffer);
  uint32_t find_memory_type(uint32_t typeFilter, VkMemoryPropertyFlags properties);

private:
  vk::structure::Vulkan* struct_vulkan;
  VK_command* vk_command;
};
