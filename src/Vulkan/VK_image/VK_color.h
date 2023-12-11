#pragma once

#include <VK_struct/Namespace.h>
#include <UTL_specific/common.h>


class VK_image;


class VK_color
{
public:
  //Constructor / Destructor
  VK_color(vk::structure::Struct_vulkan* struct_vulkan);
  ~VK_color();

public:
  //Main functions
  void create_color_attachment(vk::structure::Image* color);

  //Subfunction
  VkSurfaceFormatKHR retrieve_surface_format(const std::vector<VkSurfaceFormatKHR>& dev_format);
  VkFormat find_color_format();

private:
  vk::structure::Struct_vulkan* struct_vulkan;
  VK_image* vk_image;
};
