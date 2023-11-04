#ifndef VULKAN_BACKEND_H
#define VULKAN_BACKEND_H

#include <ELE_specific/common.h>

class Engine;
class VK_engine;


class Vulkan
{
public:
  //Constructor / Destructor
  Vulkan(Engine* engine);
  ~Vulkan();

public:
  //Main functions
  void init();
  void clean();
  void loop_draw_frame();
  void device_wait_idle();

private:
  VK_engine* vk_engine;
};

#endif
