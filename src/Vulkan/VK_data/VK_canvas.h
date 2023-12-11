#pragma once

#include <VK_struct/Namespace.h>
#include <UTL_specific/common.h>


class VK_buffer;
class VK_data;


class VK_canvas
{
public:
  //Constructor / Destructor
  VK_canvas(vk::structure::Struct_vulkan* struct_vulkan);
  ~VK_canvas();

public:
  //Main functions
  void create_canvas();
  void clean_canvas();

private:
  vk::structure::Struct_vulkan* struct_vulkan;
  VK_buffer* vk_buffer;
  VK_data* vk_data;
};
