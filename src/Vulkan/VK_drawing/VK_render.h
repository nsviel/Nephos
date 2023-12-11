#pragma once

#include <VK_struct/Struct_vk_renderpass.h>
#include <VK_struct/Namespace.h>
#include <UTL_specific/common.h>

class Struct_vulkan;
class VK_command;
class VK_submit;


class VK_render
{
public:
  //Constructor / Destructor
  VK_render(Struct_vulkan* struct_vulkan);
  ~VK_render();

public:
  //Main functions
  void run_renderpass(Struct_vk_renderpass* renderpass);
  void submit_command(Struct_vk_renderpass* renderpass);

  //Subfunction
  void start_renderpass(Struct_vk_renderpass* renderpass);
  void draw_subpass(Struct_vk_renderpass* renderpass);
  void wait_end_rendering(VkFence& fence);

private:
  Struct_vulkan* struct_vulkan;
  VK_command* vk_command;
  VK_submit* vk_submit;
};
