#ifndef VK_DEPTH_H
#define VK_DEPTH_H

#include "../VK_struct/struct_frame.h"
#include <ELE_specific/common.h>

class VK_engine;
class struct_vulkan;
class VK_image;


class VK_depth
{
public:
  //Constructor / Destructor
  VK_depth(VK_engine* vk_engine);
  ~VK_depth();

public:
  //Main functions
  void create_depth_attachment(Frame* image);
  void clean_depth_attachment(Frame* image);

  //Subfunctions
  bool find_stencil_component(VkFormat format);
  VkFormat find_supported_format(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);
  VkFormat find_depth_format();

private:
  VK_engine* vk_engine;
  struct_vulkan* vk_struct;
  VK_image* vk_image;
};

#endif
