#pragma once

#include <Utility/Specific/Common.h>

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
}

namespace vk::image{class Image;}
namespace vk::structure{class Vulkan;}
namespace vk::structure{class Image;}
namespace vk::command{class Command_buffer;}
namespace vk::command{class Allocator;}
namespace vk::memory{class Transfer;}
namespace vk::memory{class Allocator;}


namespace vk::image{

class Screenshot
{
public:
  //Constructor / Destructor
  Screenshot(vk::structure::Vulkan* struct_vulkan);
  ~Screenshot();

public:
  //Main functions
  void export_image_to_jpeg(vk::structure::Image* image);
  void export_image_to_binary(vk::structure::Image* image);

  //Subfunction
  VkDeviceSize calculate_image_size(VkFormat format, VkExtent3D extent);

private:
  vk::structure::Vulkan* struct_vulkan;
  vk::image::Image* vk_image;
  vk::command::Command_buffer* vk_command_buffer;
  vk::command::Allocator* vk_command_allocator;
  vk::memory::Transfer* vk_mem_transfer;
  vk::memory::Allocator* vk_mem_allocator;
};

}
