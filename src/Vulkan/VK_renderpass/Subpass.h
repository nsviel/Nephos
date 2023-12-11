#pragma once

#include <VK_struct/Struct_vk_renderpass.h>
#include <UTL_specific/common.h>

class Struct_vulkan;
class VK_command;
class VK_color;
class VK_depth;


namespace vk{

class Subpass
{
public:
  //Constructor / Destructor
  Subpass(Struct_vulkan* struct_vulkan);
  ~Subpass();

public:
  //Main functions
  void create_subpass(Struct_vk_renderpass* renderpass);

  //Subfunction
  void create_subpass_shader(Struct_vk_subpass* subpass);
  void create_subpass_transfert(Struct_vk_subpass* subpass);
  void create_subpass_presentation(Struct_vk_subpass* subpass);
  void create_subpass_description(Struct_vk_subpass* subpass);

  //Color attachment
  void color_attachment_description(Struct_vk_attachment& color);
  void color_attachment_reference(Struct_vk_attachment& color);

  //Depth attachment
  void depth_attachment_description(Struct_vk_attachment& depth);
  void depth_attachment_reference(Struct_vk_attachment& depth);

private:
  Struct_vulkan* struct_vulkan;
  VK_command* vk_command;
  VK_color* vk_color;
  VK_depth* vk_depth;
};

}
