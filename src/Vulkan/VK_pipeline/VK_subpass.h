#ifndef VK_SUBPASS_H
#define VK_SUBPASS_H

#include "../VK_struct/struct_renderpass.h"
#include <ELE_specific/common.h>

class VK_engine;
class Struct_vulkan;
class VK_color;
class VK_depth;


class VK_subpass
{
public:
  //Constructor / Destructor
  VK_subpass(VK_engine* vk_engine);
  ~VK_subpass();

public:
  //Main functions
  void create_subpass_presentation(Struct_renderpass* renderpass);
  void create_subpass_shader(Struct_renderpass* renderpass);

  //Subfunction
  void create_depth_attachment(Struct_subpass* subpass);
  void create_color_attachment(Struct_subpass* subpass);
  void create_subpass_description(Struct_subpass* subpass);

private:
  VK_engine* vk_engine;
  Struct_vulkan* struct_vulkan;
  VK_color* vk_color;
  VK_depth* vk_depth;
};

#endif
