#pragma once

#include <VK_main/VK_engine.h>
#include <VK_main/VK_info.h>
#include <GUI_main/GUI_nsp.h>

class GUI;
class Vulkan;
class VK_engine;
class VK_render;
class VK_imgui;

namespace gui{
class GUI_renderpass;


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
  void new_frame();

  inline Vulkan* get_vulkan(){return vulkan;}

private:
  gui::GUI_renderpass* gui_renderpass;
  Vulkan* vulkan;
  VK_engine* vk_engine;
  VK_render* vk_render;
  VK_imgui* vk_imgui;
};

}
