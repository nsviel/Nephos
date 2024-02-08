#pragma once

#include <Utility/Specific/common.h>

namespace vk::structure{class Vulkan;}
namespace vk::structure{class Image;}
namespace vk::structure{class Buffer;}


namespace vk::command{

class Memory
{
public:
  //Constructor / Destructor
  Memory(vk::structure::Vulkan* struct_vulkan);
  ~Memory();

public:
  //Image memory
  void allocate_image_memory(vk::structure::Image* image);

  //Buffer memory
  void create_empty_stagger_buffer(vk::structure::Buffer* buffer, VkDeviceSize size);
  void create_empty_vertex_buffer(vk::structure::Buffer* buffer, VkDeviceSize size);

  //Subfunction
  void bind_buffer_memory(VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
  void create_gpu_buffer(VkDeviceSize size, VkBufferUsageFlags usage, VkBuffer& buffer);
  uint32_t find_memory_type(uint32_t typeFilter, VkMemoryPropertyFlags properties);

private:
  vk::structure::Vulkan* struct_vulkan;
};

}
