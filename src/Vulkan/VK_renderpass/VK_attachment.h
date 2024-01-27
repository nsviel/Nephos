#pragma once

#include <Utility/Specific/common.h>

namespace vk::image{class Color;}
namespace vk::image{class Depth;}
namespace vk::structure{class Vulkan;}
namespace vk::structure{class Attachment;}


namespace vk::renderpass{

class VK_attachment
{
public:
  //Constructor / Destructor
  VK_attachment(vk::structure::Vulkan* struct_vulkan);
  ~VK_attachment();

public:
  //Color attachment
  void color_description(vk::structure::Attachment& color);
  void color_reference(vk::structure::Attachment& color);
  void color_resolve_description(vk::structure::Attachment& color);
  void color_resolve_reference(vk::structure::Attachment& color);

  //Depth attachment
  void depth_description(vk::structure::Attachment& depth);
  void depth_reference(vk::structure::Attachment& depth);

private:
  vk::structure::Vulkan* struct_vulkan;
  vk::image::Color* vk_color;
  vk::image::Depth* vk_depth;
};

}
