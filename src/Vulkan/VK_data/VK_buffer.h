#ifndef VK_BUFFER_H
#define VK_BUFFER_H

#include <VK_struct/Struct_entity.h>
#include <UTL_specific/common.h>

class Struct_vulkan;
class VK_command;


class VK_buffer
{
public:
  //Constructor / Destructor
  VK_buffer(Struct_vulkan* struct_vulkan);
  ~VK_buffer();

public:
  //Main functions
  void create_buffers(Struct_entity* data);
  void clean_buffers(Struct_entity* data);

  //Data buffer functions
  template <typename VertexType> void create_buffer(Struct_buffer* buffer, vector<VertexType>& vertices);
  void clean_buffer(Struct_buffer* buffer);

  //Buffer functions
  void bind_buffer_memory(VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
  void create_gpu_buffer(VkDeviceSize size, VkBufferUsageFlags usage, VkBuffer& buffer);
  void copy_buffer_to_gpu(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
  uint32_t find_memory_type(uint32_t typeFilter, VkMemoryPropertyFlags properties);

private:
  Struct_vulkan* struct_vulkan;
  VK_command* vk_command;
};

#endif
