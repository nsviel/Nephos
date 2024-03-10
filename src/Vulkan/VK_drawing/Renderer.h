#pragma once

#include <Utility/Specific/common.h>

namespace vk::command{class Command_buffer;}
namespace vk::command{class Allocator;}
namespace vk::structure{class Vulkan;}
namespace vk::structure{class Fence;}
namespace vk::structure{class Renderpass;}
namespace vk::structure{class Command_buffer;}


namespace vk::draw{

class Renderer
{
public:
  //Constructor / Destructor
  Renderer(vk::structure::Vulkan* struct_vulkan);
  ~Renderer();

public:
  //Main functions
  void run_renderpass(vk::structure::Renderpass* renderpass);

  //Subfunction
  void start_renderpass(vk::structure::Renderpass* renderpass);
  void stop_renderpass(vk::structure::Renderpass* renderpass);
  void draw_subpass(vk::structure::Renderpass* renderpass);

private:
  vk::structure::Vulkan* struct_vulkan;
  vk::command::Command_buffer* vk_command_buffer;
  vk::command::Allocator* vk_allocator;
};

}
