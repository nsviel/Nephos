#pragma once

#include <Utility/Specific/common.h>

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
}

namespace vk::image{class Image;}
namespace vk::command{class Command;}
namespace vk::main{class Texture;}
namespace vk::command{class Memory;}
namespace vk::structure{class Vulkan;}
namespace vk::structure{class Image;}
namespace vk::command{class Command_buffer;}


namespace vk::image{

class Screenshot
{
public:
  //Constructor / Destructor
  Screenshot(vk::structure::Vulkan* struct_vulkan);
  ~Screenshot();

public:
  //Main functions
  void make_screenshot(vk::structure::Image* image);
  void save_to_bin(vk::structure::Image* image);

  //Subfunction
  VkDeviceSize calculate_image_size(VkFormat format, VkExtent3D extent);

private:
  vk::structure::Vulkan* struct_vulkan;
  vk::command::Memory* vk_memory;
  vk::image::Image* vk_image;
  vk::command::Command* vk_command;
  vk::main::Texture* vk_texture;
  vk::command::Command_buffer* vk_command_buffer;
};

}
