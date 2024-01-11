#pragma once

#include <Vulkan/VK_struct/Namespace.h>
#include <Utility/Specific/common.h>


class VK_buffer;
class VK_data;


class VK_canvas
{
public:
  //Constructor / Destructor
  VK_canvas(vk::structure::Vulkan* struct_vulkan);
  ~VK_canvas();

public:
  //Main functions
  void init();
  void clean();

private:
  vk::structure::Vulkan* struct_vulkan;
  VK_buffer* vk_buffer;
  VK_data* vk_data;
};
