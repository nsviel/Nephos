#ifndef VULKAN_BACKEND_H
#define VULKAN_BACKEND_H

#include <ELE_specific/common.h>

class ELE_window;
class VK_engine;
class VK_imgui;
class VK_render;


class Vulkan
{
public:
  //Constructor / Destructor
  Vulkan(ELE_window* window);
  ~Vulkan();

public:
  //Main functions
  void init();
  void clean();
  void loop();
  void wait_idle();

  inline VK_imgui* get_vk_imgui(){return vk_imgui;}

private:
  VK_engine* vk_engine;
  VK_imgui* vk_imgui;
  VK_render* vk_render;
};

#endif
