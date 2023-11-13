#ifndef VK_SUBPASS_H
#define VK_SUBPASS_H

#include <VK_struct/Struct_renderpass.h>
#include <ELE_specific/common.h>

class Struct_vulkan;
class VK_command;
class VK_color;
class VK_depth;


class VK_subpass
{
public:
  //Constructor / Destructor
  VK_subpass(Struct_vulkan* struct_vulkan);
  ~VK_subpass();

public:
  //Main functions
  void create_subpass(Struct_renderpass* renderpass);

  //Subfunction
  void create_subpass_shader(Struct_subpass* subpass);
  void create_subpass_transfert(Struct_subpass* subpass);
  void create_subpass_presentation(Struct_subpass* subpass);
  void create_subpass_description(Struct_subpass* subpass);

  //Color attachment
  void color_attachment_description(Struct_attachment& color);
  void color_attachment_reference(Struct_attachment& color);

  //Depth attachment
  void depth_attachment_description(Struct_attachment& depth);
  void depth_attachment_reference(Struct_attachment& depth);

private:
  Struct_vulkan* struct_vulkan;
  VK_command* vk_command;
  VK_color* vk_color;
  VK_depth* vk_depth;
};

#endif
