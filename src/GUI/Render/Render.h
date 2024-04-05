#pragma once

namespace vk{class Node;}
namespace vk::draw{class Renderer;}
namespace vk::main{class Imgui;}
namespace gui{class Node;}


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
  void render();
  void clean();
  void new_frame();

  inline vk::Node* get_vulkan(){return vulkan;}

private:
  vk::Node* vulkan;
  vk::draw::Renderer* vk_render;
  vk::main::Imgui* vk_imgui;
};

}
