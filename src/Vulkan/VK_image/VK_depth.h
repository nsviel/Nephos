#ifndef VK_DEPTH_H
#define VK_DEPTH_H

#include <VK_struct/Struct_vk_framebuffer.h>
#include <UTL_specific/common.h>

class Struct_vulkan;
class VK_image;


class VK_depth
{
public:
  //Constructor / Destructor
  VK_depth(Struct_vulkan* struct_vulkan);
  ~VK_depth();

public:
  //Main functions
  void create_depth_attachment(Struct_image* depth);
  void clean_depth_attachment(Struct_image* depth);

  //Subfunctions
  bool find_stencil_component(VkFormat format);
  VkFormat find_supported_format(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);
  VkFormat find_depth_format();

private:
  Struct_vulkan* struct_vulkan;
  VK_image* vk_image;
};

#endif
