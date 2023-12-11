#pragma once

#include <VK_struct/Namespace.h>
#include <VK_struct/VK_typedef.h>
#include <UTL_specific/common.h>

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
}

class Struct_vulkan;
class VK_image;
class VK_command;
class VK_texture;
class VK_memory;


class VK_screenshot
{
public:
  //Constructor / Destructor
  VK_screenshot(Struct_vulkan* struct_vulkan);
  ~VK_screenshot();

public:
  //Main functions
  void make_screenshot(vk::structure::Struct_vk_image* image);
  void save_to_bin(vk::structure::Struct_vk_image* image);

  //Subfunction
  VkDeviceSize calculate_image_size(VkFormat format, VkExtent3D extent);

private:
  Struct_vulkan* struct_vulkan;
  VK_memory* vk_memory;
  VK_image* vk_image;
  VK_command* vk_command;
  VK_texture* vk_texture;
};
