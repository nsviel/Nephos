#ifndef VK_RENDER_H
#define VK_RENDER_H

#include <ELE_specific/common.h>

class VK_engine;
class VK_drawing;
class FPS_counter;
class Struct_vulkan;


class VK_render
{
public:
  //Constructor / Destructor
  VK_render(VK_engine* vk_engine);
  ~VK_render();

public:
  //Main functions
  void loop_draw_frame();

private:
  FPS_counter* fps_counter;
  Struct_vulkan* struct_vulkan;
  VK_drawing* vk_drawing;
};

#endif
