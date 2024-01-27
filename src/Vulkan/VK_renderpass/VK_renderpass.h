#pragma once

#include <Utility/Specific/common.h>

namespace vk::renderpass{class Pipeline;}
namespace vk::renderpass{class Framebuffer;}
namespace vk::command{class Command;}
namespace vk::renderpass{class Subpass;}
namespace vk::structure{class Vulkan;}
namespace vk::structure{class Renderpass;}


namespace vk::renderpass{

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
  vk::renderpass::Pipeline* vk_pipeline;
  Subpass* vk_subpass;
  vk::renderpass::Framebuffer* vk_framebuffer;
  vk::command::Command* vk_command;
};

}
