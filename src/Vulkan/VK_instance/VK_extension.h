#pragma once

#include <Vulkan/VK_struct/Namespace.h>
#include <Utility/Specific/common.h>


class VK_extension
{
public:
  //Constructor / Destructor
  VK_extension(vk::structure::Vulkan* struct_vulkan);
  ~VK_extension();

public:
  //Main functions
  void init();

  //Subfunction
  void extension_instance();
  void extension_window();
  void extension_device();

private:
  vk::structure::Vulkan* struct_vulkan;
};
