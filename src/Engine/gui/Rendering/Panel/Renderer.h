#pragma once

#include <Utility/Specific/Common.h>

namespace vk::gui{class Imgui;}
namespace vk::main{class Interface;}
namespace eng{class Node;}
namespace eng::cam::gui{class Control;}
namespace ope{class Node;}


namespace eng::gui{

class Renderer
{
public:
  //Constructor / Destructor
  Renderer(eng::Node* node_engine);
  ~Renderer();

public:
  //Main functions
  void run_panel();
  void design_panel();

  //Subfunction
  void engine_texture();
  void resize();

private:
  eng::cam::gui::Control* cam_control;
  ope::Node* node_operation;
  vk::gui::Imgui* vk_imgui;
  vk::main::Interface* vk_interface;

  string name;
  bool has_been_initialized;
};

}
