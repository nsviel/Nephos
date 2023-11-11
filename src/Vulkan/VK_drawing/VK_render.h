#ifndef VK_RENDER_H
#define VK_RENDER_H

#include <ELE_specific/common.h>

class Struct_vulkan;


class VK_render
{
public:
  //Constructor / Destructor
  VK_render(Struct_vulkan* struct_vulkan);
  ~VK_render();

public:
  //Main functions

private:
  Struct_vulkan* struct_vulkan;
};

#endif
