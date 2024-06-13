#pragma once

#include <Utility/Specific/Common.h>

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
}

namespace vk::image{class Image;}
namespace vk::image{class Transition;}
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
  Screenshot(vk::structure::Vulkan* vk_struct);
  ~Screenshot();

public:
  //Main function
  void make_screenshot();
  void export_image_to_jpeg(vk::structure::Image* image);
  void export_image_to_bmp(vk::structure::Image* image);
  void export_image_to_binary(vk::structure::Image* image);

  //Subfunction
  VkDeviceSize calculate_image_size(VkFormat format, VkExtent3D extent);

private:
  vk::structure::Vulkan* vk_struct;
  vk::image::Image* vk_image;
  vk::image::Transition* vk_transition;
  vk::command::Command_buffer* vk_command_buffer;
  vk::command::Allocator* vk_command_allocator;
  vk::memory::Transfer* vk_mem_transfer;
  vk::memory::Allocator* vk_mem_allocator;
};

}
