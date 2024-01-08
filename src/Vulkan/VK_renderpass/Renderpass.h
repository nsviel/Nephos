#pragma once

#include <Utility/Specific/common.h>
#include <Vulkan/VK_main/Namespace.h>


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
  void init_all_renderpass();
  void clean_all_renderpass();

  //Subfunction
  void create_renderpass(vk::structure::Renderpass* renderpass);
  void clean_renderpass(vk::structure::Renderpass* renderpass);

private:
  vk::structure::Vulkan* struct_vulkan;
  VK_pipeline* vk_pipeline;
  vk::Subpass* vk_subpass;
  VK_framebuffer* vk_framebuffer;
  VK_command* vk_command;
};

}
