#pragma once

#include <VK_struct/Namespace.h>
#include <UTL_specific/common.h>




class VK_submit
{
public:
  //Constructor / Destructor
  VK_submit(vk::structure::Struct_vulkan* struct_vulkan);
  ~VK_submit();

public:
  //Main functions
  void submit_command_graphics(VkCommandBuffer command);
  void submit_command_render(vk::structure::Command* commands);

private:
  vk::structure::Struct_vulkan* struct_vulkan;
};
