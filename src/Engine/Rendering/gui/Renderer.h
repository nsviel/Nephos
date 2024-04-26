#pragma once

#include <Utility/Specific/Common.h>

namespace vk::gui{class Imgui;}
namespace vk::main{class Interface;}
namespace vk::structure{class Vulkan;}
namespace eng{class Node;}
namespace eng::cam::gui{class Control;}
namespace ope{class Node;}
namespace engine = eng;


namespace rnd::gui{

class Renderer
{
public:
  //Constructor / Destructor
  Renderer(engine::Node* node_engine);
  ~Renderer();

public:
  //Main functions
  void run_panel();
  void design_panel();

  //Subfunction
  void engine_texture();
  void resize();

private:
  engine::cam::gui::Control* cam_control;
  ope::Node* node_operation;
  vk::gui::Imgui* vk_imgui;
  vk::main::Interface* vk_interface;
  vk::structure::Vulkan* vk_struct;

  string name;
  bool has_been_initialized;
};

}
