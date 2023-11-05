#ifndef VK_CANVAS_H
#define VK_CANVAS_H

#include "../VK_struct/struct_data.h"
#include <ELE_specific/common.h>

class VK_engine;
class Struct_vulkan;
class VK_buffer;
class VK_data;
class VK_texture;
class VK_binding;


class VK_canvas
{
public:
  //Constructor / Destructor
  VK_canvas(VK_engine* vk_engine);
  ~VK_canvas();

public:
  //Main functions
  void create_canvas();
  void clean_canvas();

private:
  Struct_vulkan* struct_vulkan;
  VK_buffer* vk_buffer;
  VK_data* vk_data;
  VK_texture* vk_texture;
  VK_binding* vk_binding;
};

#endif
