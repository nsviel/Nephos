#pragma once

#include <Utility/Specific/common.h>

class VK_profiler;
namespace vk::command{class Command;}
namespace vk::command{class Submit;}
namespace vk::structure{class Vulkan;}
namespace vk::structure{class Renderpass;}


namespace vk::draw{

class VK_render
{
public:
  //Constructor / Destructor
  VK_render(vk::structure::Vulkan* struct_vulkan);
  ~VK_render();

public:
  //Main functions
  void run_renderpass(vk::structure::Renderpass* renderpass);
  void submit_command(vk::structure::Renderpass* renderpass);

  //Subfunction
  void start_renderpass(vk::structure::Renderpass* renderpass);
  void draw_subpass(vk::structure::Renderpass* renderpass);
  void wait_end_rendering(VkFence& fence);

private:
  vk::structure::Vulkan* struct_vulkan;
  vk::command::Command* vk_command;
  vk::command::Submit* vk_submit;
  VK_profiler* vk_profiler;
};

}
