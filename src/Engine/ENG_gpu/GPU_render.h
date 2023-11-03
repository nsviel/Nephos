#ifndef GPU_RENDER_H
#define GPU_RENDER_H

#include <ELE_specific/common.h>

class VK_engine;
class Struct_vulkan;


class GPU_render
{
public:
  //Constructor / Destructor
  GPU_render(VK_engine* vk_engine);
  ~GPU_render();

public:
  //Main functions

private:
  Struct_vulkan* vk_struct;
};

#endif
