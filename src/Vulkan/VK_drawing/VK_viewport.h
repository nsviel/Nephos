#pragma once

#include <VK_struct/Namespace.h>
#include <UTL_specific/common.h>




class VK_viewport
{
public:
  VK_viewport(vk::structure::Struct_vulkan* struct_vulkan);
  ~VK_viewport();

public:
  //Main function
  void init_viewport();
  void cmd_viewport(VkCommandBuffer& command_buffer);
  void update_viewport();

  //Subfunction
  vk::structure::Viewport* create_viewport();

private:
  vk::structure::Struct_vulkan* struct_vulkan;
};
