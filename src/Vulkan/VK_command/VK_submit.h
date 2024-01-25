#pragma once

#include <Utility/Specific/common.h>

namespace vk::structure{class Vulkan;}
namespace vk::structure{class Command;}


class VK_submit
{
public:
  //Constructor / Destructor
  VK_submit(vk::structure::Vulkan* struct_vulkan);
  ~VK_submit();

public:
  //Main functions
  void submit_command_graphics(VkCommandBuffer command);
  void submit_command_render(vk::structure::Command* commands);

private:
  vk::structure::Vulkan* struct_vulkan;
};
