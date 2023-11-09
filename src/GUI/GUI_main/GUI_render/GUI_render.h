#ifndef GUI_RENDER_H
#define GUI_RENDER_H

#include <VK_main/VK_engine.h>
#include <VK_main/VK_info.h>

class GUI;
class GUI_renderpass;
class Vulkan;
class VK_engine;
class VK_render;


class GUI_render
{
public:
  //Constructor / Destructor
  GUI_render(GUI* gui);
  ~GUI_render();

public:
  //Main functions
  void init();
  void loop();
  void clean();
  void wait();

  inline Vulkan* get_gui_vulkan(){return gui_vulkan;}

private:
  GUI_renderpass* gui_renderpass;
  Vulkan* gui_vulkan;
  VK_engine* vk_engine;
  VK_render* vk_render;
};

#endif
