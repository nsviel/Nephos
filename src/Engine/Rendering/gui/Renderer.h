#pragma once

#include <Utility/Specific/Common.h>

namespace rnd{class Node;}
namespace vk::gui{class Imgui;}
namespace vk::main{class Interface;}
namespace vk::structure{class Vulkan;}
namespace eng{class Node;}
namespace eng::cam::gui{class Control;}
namespace rnd::gui{class Control;}
namespace engine = eng;


namespace rnd::gui{

class Renderer
{
public:
  //Constructor / Destructor
  Renderer(rnd::Node* node_rendering);
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
  rnd::gui::Control* gui_control;
  vk::gui::Imgui* vk_imgui;
  vk::main::Interface* vk_interface;
  vk::structure::Vulkan* vk_struct;

  string name;
  bool has_been_initialized;
};

}
