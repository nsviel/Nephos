#pragma once

#include <Utility/Specific/common.h>

namespace vk::command{class Command_buffer;}
namespace vk::command{class Command;}
namespace vk::image{class Image;}
namespace vk::structure{class Vulkan;}
namespace vk::structure{class Image;}
namespace vk::structure{class Texture;}
namespace vk::structure{class Command_buffer;}
namespace vk::structure{class Buffer;}


namespace vk::command{

class Transfert
{
public:
  //Constructor / Destructor
  Transfert(vk::structure::Vulkan* struct_vulkan);
  ~Transfert();

public:
  //Image GPU function
  void transfert_texture_to_gpu(vk::structure::Texture* texture);
  void copy_buffer_to_image(vk::structure::Command_buffer* command_buffer, vk::structure::Image* image, VkBuffer buffer);
  void copy_image_to_buffer(vk::structure::Command_buffer* command_buffer, vk::structure::Image* image, VkBuffer buffer);

  //Buffer GPU function
  void update_buffer_data(vk::structure::Buffer* buffer, const void* data, VkDeviceSize dataSize);
  void update_buffer_data(vk::structure::Buffer* buffer, vk::structure::Buffer* stagger, const void* data, VkDeviceSize dataSize);

private:
  vk::structure::Vulkan* struct_vulkan;
  vk::image::Image* vk_image;
  vk::command::Command* vk_command;
  vk::command::Command_buffer* vk_command_buffer;
};

}
