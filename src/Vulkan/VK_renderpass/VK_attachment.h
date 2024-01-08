#pragma once

#include <Vulkan/VK_struct/Namespace.h>
#include <Utility/Specific/common.h>

class VK_color;
class VK_depth;


class VK_attachment
{
public:
  //Constructor / Destructor
  VK_attachment(vk::structure::Vulkan* struct_vulkan);
  ~VK_attachment();

public:
  //Color attachment
  void color_attachment_description(vk::structure::Attachment& color);
  void color_attachment_reference(vk::structure::Attachment& color);
  void color_attachment_resolve_description(vk::structure::Attachment& color);
  void color_attachment_resolve_reference(vk::structure::Attachment& color);

  //Depth attachment
  void depth_attachment_description(vk::structure::Attachment& depth);
  void depth_attachment_reference(vk::structure::Attachment& depth);

private:
  vk::structure::Vulkan* struct_vulkan;
  VK_color* vk_color;
  VK_depth* vk_depth;
};
