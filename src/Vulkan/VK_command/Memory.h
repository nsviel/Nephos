#pragma once

#include <Utility/Specific/common.h>

namespace vk::command{class Command;}
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
  //Image GPU function
  void transfert_image_to_gpu(vk::structure::Image* image);
  void allocate_image_memory(vk::structure::Image* image);
  void copy_buffer_to_image(vk::structure::Image* image, VkBuffer buffer);
  void copy_image_to_buffer(vk::structure::Image* image, VkBuffer buffer);

  //Buffer GPU function
  void create_buffer_to_gpu(vector<vec2>& vertices, vk::structure::Buffer* buffer);
  void create_buffer_to_gpu(vector<vec3>& vertices, vk::structure::Buffer* buffer);
  void create_buffer_to_gpu(vector<vec4>& vertices, vk::structure::Buffer* buffer);
  void copy_buffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);

  void update_buffer_to_gpu(vector<vec2>& vertices, vk::structure::Buffer* buffer);
  void update_buffer_to_gpu(vector<vec3>& vertices, vk::structure::Buffer* buffer);
  void update_buffer_to_gpu(vector<vec4>& vertices, vk::structure::Buffer* buffer);

  //Subfunction
  void bind_buffer_memory(VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
  void create_gpu_buffer(VkDeviceSize size, VkBufferUsageFlags usage, VkBuffer& buffer);
  uint32_t find_memory_type(uint32_t typeFilter, VkMemoryPropertyFlags properties);

private:
  vk::structure::Vulkan* struct_vulkan;
  vk::command::Command* vk_command;
};

}
