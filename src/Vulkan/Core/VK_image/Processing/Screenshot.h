#pragma once

#include <vulkan/vulkan.h>

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
}

namespace vk{class Structure;}
namespace vk::image{class Image;}
namespace vk::structure{class Image;}
namespace vk::commandbuffer{class Command_buffer;}
namespace vk::commandbuffer{class Allocator;}
namespace vk::memory{class Transfer;}
namespace vk::memory{class Allocator;}


namespace vk::image{

class Screenshot
{
public:
  //Constructor / Destructor
  Screenshot(vk::Structure* vk_struct);
  ~Screenshot();

public:
  //Main function
  void make_screenshot();
  void export_image_to_jpeg(vk::structure::Image& image);
  void export_image_to_bmp(vk::structure::Image& image);
  void export_image_to_binary(vk::structure::Image& image);

  //Subfunction
  VkDeviceSize calculate_image_size(VkFormat format, VkExtent3D extent);

private:
  vk::Structure* vk_struct;
  vk::image::Image* vk_image;
  vk::commandbuffer::Command_buffer* vk_command_buffer;
  vk::commandbuffer::Allocator* vk_command_allocator;
  vk::memory::Transfer* vk_mem_transfer;
  vk::memory::Allocator* vk_mem_allocator;
};

}
