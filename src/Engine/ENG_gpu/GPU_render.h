#ifndef GPU_RENDER_H
#define GPU_RENDER_H

#include <ELE_specific/common.h>

class VK_engine;
class struct_vulkan;


class GPU_render
{
public:
  //Constructor / Destructor
  GPU_render(VK_engine* vk_engine);
  ~GPU_render();

public:
  //Main functions

private:
  struct_vulkan* vk_struct;
};

#endif
