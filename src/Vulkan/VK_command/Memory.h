#pragma once

#include <Utility/Specific/common.h>

namespace vk::command{class Command_buffer;}
namespace vk::command{class Command;}
namespace vk::structure{class Vulkan;}
namespace vk::structure{class Image;}
namespace vk::structure{class Texture;}
namespace vk::structure{class Command_buffer;}
namespace vk::structure{class Buffer;}


namespace vk::command{

class Memory
{
public:
  //Constructor / Destructor
  Memory(vk::structure::Vulkan* struct_vulkan);
  ~Memory();

public:
  //Image GPU function
  void transfert_texture_to_gpu(vk::structure::Texture* texture);
  void allocate_image_memory(vk::structure::Image* image);
  void copy_buffer_to_image(vk::structure::Command_buffer* command_buffer, vk::structure::Image* image, VkBuffer buffer);
  void copy_image_to_buffer(vk::structure::Command_buffer* command_buffer, vk::structure::Image* image, VkBuffer buffer);

  //Buffer GPU function
  void create_empty_stagger_buffer(vk::structure::Buffer* buffer, VkDeviceSize size);
  void create_empty_vertex_buffer(vk::structure::Buffer* buffer, VkDeviceSize size);
  void update_buffer_data(vk::structure::Buffer* buffer, const void* data, VkDeviceSize dataSize);
  void update_buffer_data(vk::structure::Buffer* buffer, vk::structure::Buffer* stagger, const void* data, VkDeviceSize dataSize);
  void copy_buffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);

  //Subfunction
  void bind_buffer_memory(VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
  void create_gpu_buffer(VkDeviceSize size, VkBufferUsageFlags usage, VkBuffer& buffer);
  uint32_t find_memory_type(uint32_t typeFilter, VkMemoryPropertyFlags properties);

private:
  vk::structure::Vulkan* struct_vulkan;
  vk::command::Command* vk_command;
  vk::command::Command_buffer* vk_command_buffer;
};

}
