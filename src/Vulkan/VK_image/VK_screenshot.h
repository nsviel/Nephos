#pragma once

#include <Utility/Specific/common.h>

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
}

class VK_image;
namespace vk::command{class VK_command;}
class VK_texture;
namespace vk::command{class VK_memory;}
namespace vk::structure{class Vulkan;}
namespace vk::structure{class Image;}


class VK_screenshot
{
public:
  //Constructor / Destructor
  VK_screenshot(vk::structure::Vulkan* struct_vulkan);
  ~VK_screenshot();

public:
  //Main functions
  void make_screenshot(vk::structure::Image* image);
  void save_to_bin(vk::structure::Image* image);

  //Subfunction
  VkDeviceSize calculate_image_size(VkFormat format, VkExtent3D extent);

private:
  vk::structure::Vulkan* struct_vulkan;
  vk::command::VK_memory* vk_memory;
  VK_image* vk_image;
  vk::command::VK_command* vk_command;
  VK_texture* vk_texture;
};
