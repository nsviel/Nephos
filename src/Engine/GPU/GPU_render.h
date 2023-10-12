#ifndef GPU_RENDER_H
#define GPU_RENDER_H

#include <Specific/common.h>

class VK_engine;
class VK_struct;


class GPU_render
{
public:
  //Constructor / Destructor
  GPU_render(VK_engine* vk_engine);
  ~GPU_render();

public:
  //Main functions

private:
  VK_struct* vk_struct;
};

#endif
