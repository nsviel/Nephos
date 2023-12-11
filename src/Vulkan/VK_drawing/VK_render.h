#pragma once

#include <VK_struct/Namespace.h>
#include <VK_struct/Namespace.h>
#include <UTL_specific/common.h>


class VK_command;
class VK_submit;


class VK_render
{
public:
  //Constructor / Destructor
  VK_render(vk::structure::Struct_vulkan* struct_vulkan);
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
  vk::structure::Struct_vulkan* struct_vulkan;
  VK_command* vk_command;
  VK_submit* vk_submit;
};
