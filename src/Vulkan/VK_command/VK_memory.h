#ifndef VK_MEMORY_H
#define VK_MEMORY_H

#include <VK_struct/Struct_vk_buffer.h>
#include <VK_struct/Struct_vk_image.h>
#include <UTL_specific/common.h>

class Struct_vulkan;
class VK_command;


class VK_memory
{
public:
  //Constructor / Destructor
  VK_memory(Struct_vulkan* struct_vulkan);
  ~VK_memory();

public:
  //Image GPU function
  void transfert_image_to_gpu(Struct_vk_image* image);
  void allocate_image_memory(Struct_vk_image* image);
  void copy_buffer_to_image(Struct_vk_image* image, VkBuffer buffer);
  void copy_image_to_buffer(Struct_vk_image* image, VkBuffer buffer);

  //Buffer GPU function
  void transfert_buffer_to_gpu(Struct_vk_buffer* buffer, vector<vec2>& vertices);
  void transfert_buffer_to_gpu(Struct_vk_buffer* buffer, vector<vec3>& vertices);
  void transfert_buffer_to_gpu(Struct_vk_buffer* buffer, vector<vec4>& vertices);
  void copy_buffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);

  //Subfunction
  void bind_buffer_memory(VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
  void create_gpu_buffer(VkDeviceSize size, VkBufferUsageFlags usage, VkBuffer& buffer);
  uint32_t find_memory_type(uint32_t typeFilter, VkMemoryPropertyFlags properties);

private:
  Struct_vulkan* struct_vulkan;
  VK_command* vk_command;
};

#endif
