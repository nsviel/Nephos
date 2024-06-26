#pragma once

#include <vulkan/vulkan.h>

namespace vk::structure{class Vulkan;}
namespace vk::structure{class Image;}
namespace vk::data::structure{class Buffer;}


namespace vk::memory{

class Allocator
{
public:
  //Constructor / Destructor
  Allocator(vk::structure::Vulkan* vk_struct);
  ~Allocator();

public:
  //Image memory
  void allocate_image_memory(vk::structure::Image* image);

  //Buffer memory
  void allocate_empty_stagger_buffer(vk::data::structure::Buffer* buffer, VkDeviceSize size);
  void allocate_empty_vertex_buffer(vk::data::structure::Buffer* buffer, VkDeviceSize size);

  //Subfunction
  void bind_buffer_memory(VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
  void create_gpu_buffer(VkDeviceSize size, VkBufferUsageFlags usage, VkBuffer& buffer);
  uint32_t find_memory_type(uint32_t typeFilter, VkMemoryPropertyFlags properties);

private:
  vk::structure::Vulkan* vk_struct;
};

}
