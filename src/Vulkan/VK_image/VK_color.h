#ifndef VK_COLOR_H
#define VK_COLOR_H

#include "../VK_struct/Struct_framebuffer.h"
#include <ELE_specific/common.h>

class VK_engine;
class Struct_vulkan;
class VK_physical_device;
class VK_image;


class VK_color
{
public:
  //Constructor / Destructor
  VK_color(VK_engine* vk_engine);
  ~VK_color();

public:
  //Main functions
  void create_color_attachment(Struct_framebuffer* image);

  //Subfunction
  VkSurfaceFormatKHR retrieve_surface_format(const std::vector<VkSurfaceFormatKHR>& dev_format);
  VkFormat find_color_format();

private:
  VK_engine* vk_engine;
  Struct_vulkan* struct_vulkan;
  VK_physical_device* vk_physical_device;
  VK_image* vk_image;
};

#endif
