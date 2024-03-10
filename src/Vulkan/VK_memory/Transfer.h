#pragma once

#include <Utility/Specific/common.h>

namespace vk::command{class Command_buffer;}
namespace vk::command{class Allocator;}
namespace vk::image{class Image;}
namespace vk::structure{class Vulkan;}
namespace vk::structure{class Image;}
namespace vk::structure{class Texture;}
namespace vk::structure{class Command_buffer;}
namespace vk::structure{class Buffer;}


namespace vk::memory{

class Transfer
{
public:
  //Constructor / Destructor
  Transfer(vk::structure::Vulkan* struct_vulkan);
  ~Transfer();

public:
  //Image copy function
  void copy_texture_to_gpu(vk::structure::Texture* texture);
  void copy_buffer_to_image(vk::structure::Command_buffer* command_buffer, vk::structure::Image* image, VkBuffer buffer);
  void copy_image_to_buffer(vk::structure::Command_buffer* command_buffer, vk::structure::Image* image, VkBuffer buffer);

  //Data copy function
  void copy_data_to_gpu(vk::structure::Buffer* buffer, const void* data, VkDeviceSize dataSize);
  void copy_data_to_gpu(vk::structure::Buffer* buffer, vk::structure::Buffer* stagger, const void* data, VkDeviceSize dataSize);

private:
  vk::structure::Vulkan* struct_vulkan;
  vk::image::Image* vk_image;
  vk::command::Command_buffer* vk_command_buffer;
  vk::command::Allocator* vk_allocator;
};

}
