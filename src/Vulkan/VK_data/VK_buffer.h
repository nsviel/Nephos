#ifndef VK_BUFFER_H
#define VK_BUFFER_H

#include <VK_struct/Struct_entity.h>
#include <ELE_specific/common.h>

class VK_engine;
class Struct_vulkan;
class VK_physical_device;
class VK_command;


class VK_buffer
{
public:
  //Constructor / Destructor
  VK_buffer(Struct_vulkan* struct_vulkan);
  ~VK_buffer();

public:
  //Main functions
  void create_buffer(Struct_entity* data);
  void clean_buffer(Struct_entity* data);

  //Data buffer functions
  void create_buffer_uv(Struct_entity* data);
  void create_buffer_xyz(Struct_entity* data);
  void create_buffer_rgb(Struct_entity* data);

  //Buffer functions
  void bind_buffer_memory(VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
  void create_gpu_buffer(VkDeviceSize size, VkBufferUsageFlags usage, VkBuffer& buffer);
  void copy_buffer_to_gpu(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);

  //Specific functions
  uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);

private:
  VK_command* vk_command;
  Struct_vulkan* struct_vulkan;
};

#endif
