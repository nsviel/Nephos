#pragma once

namespace vk{class Node;}
namespace vk::main{class VK_engine;}
namespace vk::draw{class Renderer;}
namespace vk::main{class VK_imgui;}
namespace gui{class Node;}
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

  inline vk::Node* get_vulkan(){return vulkan;}

private:
  gui::Renderpass* gui_renderpass;
  vk::Node* vulkan;
  vk::main::VK_engine* vk_engine;
  vk::draw::Renderer* vk_render;
  vk::main::VK_imgui* vk_imgui;
};

}
