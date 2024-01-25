#pragma once

#include <Utility/Specific/common.h>

class VK_pipeline;
class VK_framebuffer;
namespace vk::command{class Command;}
class VK_subpass;
namespace vk::structure{class Vulkan;}
namespace vk::structure{class Renderpass;}


class VK_renderpass
{
public:
  //Constructor / Destructor
  VK_renderpass(vk::structure::Vulkan* struct_vulkan);
  ~VK_renderpass();

public:
  //Main functions
  void init();
  void clean();

  //Subfunction
  void create_renderpass(vk::structure::Renderpass* renderpass);
  void clean_renderpass(vk::structure::Renderpass* renderpass);

private:
  vk::structure::Vulkan* struct_vulkan;
  VK_pipeline* vk_pipeline;
  VK_subpass* vk_subpass;
  VK_framebuffer* vk_framebuffer;
  vk::command::Command* vk_command;
};
