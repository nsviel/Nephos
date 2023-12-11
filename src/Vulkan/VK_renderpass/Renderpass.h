#pragma once

#include <UTL_specific/common.h>
#include <VK_main/Namespace.h>


class VK_pipeline;
class VK_framebuffer;
class VK_command;


namespace vk{
class Subpass;


class Renderpass
{
public:
  //Constructor / Destructor
  Renderpass(vk::structure::Vulkan* struct_vulkan);
  ~Renderpass();

public:
  //Main functions
  void init_renderpass();
  void clean_renderpass();

  //Subfunction
  void create_renderpass_struct(vk::structure::Renderpass* renderpass);
  void create_renderpass_obj(vk::structure::Renderpass* renderpass);
  void clean_renderpass_struct(vk::structure::Renderpass* renderpass);

private:
  vk::structure::Vulkan* struct_vulkan;
  VK_pipeline* vk_pipeline;
  vk::Subpass* vk_subpass;
  VK_framebuffer* vk_framebuffer;
  VK_command* vk_command;
};

}
