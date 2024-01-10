#pragma once

#include <Vulkan/VK_main/VK_engine.h>
#include <Vulkan/VK_main/VK_info.h>
#include <GUI/GUI_main/Namespace.h>

class GUI;
class Vulkan;
class VK_engine;
class VK_render;
class VK_imgui;

namespace gui{
class Renderpass;


class Render
{
public:
  //Constructor / Destructor
  Render(GUI* gui);
  ~Render();

public:
  //Main functions
  void init();
  void loop();
  void clean();
  void new_frame();

  inline Vulkan* get_vulkan(){return vulkan;}

private:
  gui::Renderpass* gui_renderpass;
  Vulkan* vulkan;
  VK_engine* vk_engine;
  VK_render* vk_render;
  VK_imgui* vk_imgui;
};

}
