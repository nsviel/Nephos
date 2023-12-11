#pragma once

#include <VK_struct/Struct_vk_framebuffer.h>
#include <VK_struct/Struct_vk_renderpass.h>
#include <VK_struct/Namespace.h>
#include <VK_struct/Struct_vk_swapchain.h>
#include <UTL_specific/common.h>

class Struct_vulkan;


class VK_submit
{
public:
  //Constructor / Destructor
  VK_submit(Struct_vulkan* struct_vulkan);
  ~VK_submit();

public:
  //Main functions
  void submit_command_graphics(VkCommandBuffer command);
  void submit_command_render(vk::structure::Command* commands);

private:
  Struct_vulkan* struct_vulkan;
};
