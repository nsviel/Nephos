#pragma once

#include <Utility/Specific/common.h>

namespace vk::renderpass{class Pipeline;}
namespace vk::renderpass{class Framebuffer;}
namespace vk::command{class Command;}
namespace vk::renderpass{class Subpass;}
namespace vk::structure{class Vulkan;}
namespace vk::structure{class Renderpass;}


namespace vk::renderpass{

class Renderpass
{
public:
  //Constructor / Destructor
  Renderpass(vk::structure::Vulkan* struct_vulkan);
  ~Renderpass();

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
  vk::renderpass::Subpass* vk_subpass;
  vk::renderpass::Framebuffer* vk_framebuffer;
  vk::command::Command* vk_command;
};

}
