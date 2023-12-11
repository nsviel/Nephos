#pragma once

#include <Vulkan/VK_struct/Namespace.h>
#include <Vulkan/VK_struct/Namespace.h>
#include <Utility/UTL_specific/common.h>


class VK_command;
class VK_submit;


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
  VK_command* vk_command;
  VK_submit* vk_submit;
};
