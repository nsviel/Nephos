#pragma once

#include <Utility/Specific/common.h>

namespace vk{class Node;}
namespace vk::main{class Imgui;}
namespace vk::main{class Info;}


namespace vk::render::gui{

class Renderer
{
public:
  //Constructor / Destructor
  Renderer(vk::Node* node_vulkan);
  ~Renderer();

public:
  //Main functions
  void run_panel();
  void design_panel();

  //Subfunction
  void engine_texture();
  void resize();

private:
  vk::main::Imgui* vk_imgui;
  vk::main::Info* vk_info;

  string name;
  bool has_been_initialized;
};

}
