#pragma once

#include <Vulkan/VK_struct/Namespace.h>
#include <Vulkan/VK_struct/Namespace.h>
#include <Utility/UTL_specific/common.h>


class VK_command;
class VK_color;
class VK_depth;


namespace vk{

class Subpass
{
public:
  //Constructor / Destructor
  Subpass(vk::structure::Vulkan* struct_vulkan);
  ~Subpass();

public:
  //Main functions
  void create_subpass(vk::structure::Renderpass* renderpass);

  //Subfunction
  void create_subpass_shader(vk::structure::Subpass* subpass);
  void create_subpass_transfert(vk::structure::Subpass* subpass);
  void create_subpass_presentation(vk::structure::Subpass* subpass);
  void create_subpass_description(vk::structure::Subpass* subpass);

  //Color attachment
  void color_attachment_description(vk::structure::Attachment& color);
  void color_attachment_reference(vk::structure::Attachment& color);

  //Depth attachment
  void depth_attachment_description(vk::structure::Attachment& depth);
  void depth_attachment_reference(vk::structure::Attachment& depth);

private:
  vk::structure::Vulkan* struct_vulkan;
  VK_command* vk_command;
  VK_color* vk_color;
  VK_depth* vk_depth;
};

}
