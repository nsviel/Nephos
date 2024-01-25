#pragma once

namespace gui{class Node;}
class Vulkan;
class VK_engine;
class VK_render;
class VK_imgui;

namespace gui{class Renderpass;}


namespace gui{

class Render
{
public:
  //Constructor / Destructor
  Render(gui::Node* gui);
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
