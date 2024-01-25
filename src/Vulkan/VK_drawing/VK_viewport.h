#pragma once

#include <Utility/Specific/common.h>

namespace vk::structure{class Vulkan;}
namespace vk::structure{class Viewport;}


class VK_viewport
{
public:
  VK_viewport(vk::structure::Vulkan* struct_vulkan);
  ~VK_viewport();

public:
  //Main function
  void init();
  void cmd_viewport(VkCommandBuffer& command_buffer);
  void update_viewport();

  //Subfunction
  vk::structure::Viewport* create_viewport();

private:
  vk::structure::Vulkan* struct_vulkan;
};
