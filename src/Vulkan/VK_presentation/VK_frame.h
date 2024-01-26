#pragma once

#include <Utility/Specific/common.h>

class VK_image;
namespace vk::command{class Synchronization;}
namespace vk::image{class Color;}
class VK_framebuffer;
namespace vk::image{class Depth;}
namespace vk::structure{class Vulkan;}


class VK_frame
{
public:
  //Constructor / Destructor
  VK_frame(vk::structure::Vulkan* struct_vulkan);
  ~VK_frame();

public:
  //Main function
  void create_frame();
  void clean_frame();

private:
  vk::structure::Vulkan* struct_vulkan;
  vk::command::Synchronization* vk_synchronization;
  VK_framebuffer* vk_framebuffer;
  VK_image* vk_image;
  vk::image::Color* vk_color;
  vk::image::Depth* vk_depth;
};
