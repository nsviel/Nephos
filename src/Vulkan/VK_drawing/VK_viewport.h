#pragma once

#include <VK_struct/Namespace.h>
#include <UTL_specific/common.h>

class Struct_vulkan;


class VK_viewport
{
public:
  VK_viewport(Struct_vulkan* struct_vulkan);
  ~VK_viewport();

public:
  //Main function
  void init_viewport();
  void cmd_viewport(VkCommandBuffer& command_buffer);
  void update_viewport();

  //Subfunction
  vk::structure::Struct_vk_viewport* create_viewport();

private:
  Struct_vulkan* struct_vulkan;
};
