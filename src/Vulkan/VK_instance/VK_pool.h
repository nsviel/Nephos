#pragma once

#include <Vulkan/VK_struct/Namespace.h>
#include <Utility/Specific/common.h>


class VK_pool
{
public:
  //Constructor / Destructor
  VK_pool(vk::structure::Vulkan* struct_vulkan);
  ~VK_pool();

public:
  //Main functions
  void init();
  void clean();

  //Descriptor pool
  void create_descriptor_pool();
  void reset_descriptor_pool();
  void clean_descriptor_pool();

  //Command pool
  void create_command_pool();
  void reset_command_pool();
  void clean_command_pool();

private:
  vk::structure::Vulkan* struct_vulkan;
};
