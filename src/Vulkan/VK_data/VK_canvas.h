#pragma once

#include <VK_struct/Struct_vk_entity.h>
#include <UTL_specific/common.h>

class Struct_vulkan;
class VK_buffer;
class VK_data;


class VK_canvas
{
public:
  //Constructor / Destructor
  VK_canvas(Struct_vulkan* struct_vulkan);
  ~VK_canvas();

public:
  //Main functions
  void create_canvas();
  void clean_canvas();

private:
  Struct_vulkan* struct_vulkan;
  VK_buffer* vk_buffer;
  VK_data* vk_data;
};
