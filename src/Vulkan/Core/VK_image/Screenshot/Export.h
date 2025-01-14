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
namespace vk::commandbuffer{class Pool;}
namespace vk::commandbuffer{class Allocator;}
namespace vk::memory{class Transfer;}
namespace vk::memory{class Allocator;}


namespace vk::image{

class Export
{
public:
  //Constructor / Destructor
  Export(vk::Structure* vk_struct);
  ~Export();

public:
  //Main function
  void export_image_to_jpeg(vk::structure::Image& image);
  void export_image_to_bmp(vk::structure::Image& image);
  void export_image_to_binary(vk::structure::Image& image);
  void export_depth_to_bmp(vk::structure::Image& image);
  
  //Subfunction
  VkDeviceSize calculate_image_size(VkFormat format, VkExtent3D extent);

private:
  vk::Structure* vk_struct;
  vk::image::Image* vk_image;
  vk::commandbuffer::Pool* vk_command_buffer;
  vk::commandbuffer::Allocator* vk_allocator;
  vk::memory::Transfer* vk_mem_transfer;
  vk::memory::Allocator* vk_mem_allocator;
};

}
