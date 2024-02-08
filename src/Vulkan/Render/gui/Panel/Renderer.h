#pragma once

#include <Utility/Specific/common.h>

namespace vk::main{class Imgui;}
namespace vk::main{class Info;}
namespace vk::render{class Node;}
namespace eng::cam{class Node;}
namespace eng::ope{class Node;}
namespace utl::element{class Window;}


namespace vk::render::gui{

class Renderer
{
public:
  //Constructor / Destructor
  Renderer(vk::render::Node* node_render);
  ~Renderer();

public:
  //Main functions
  void run_panel();
  void design_panel();

  //Subfunction
  void engine_texture();
  void resize();

private:
  eng::cam::Node* node_camera;
  eng::ope::Node* node_operation;
  utl::element::Window* utl_window;
  vk::main::Imgui* vk_imgui;
  vk::main::Info* vk_info;

  string name;
  bool has_been_initialized;
};

}
