#pragma once

#include <Utility/Specific/common.h>

class VK_image;
namespace vk::command{class Synchronization;}
class VK_color;
class VK_framebuffer;
class VK_depth;
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
  VK_color* vk_color;
  VK_depth* vk_depth;
};
