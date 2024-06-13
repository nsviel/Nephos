#pragma once

#include <string>

namespace rnd{class Node;}
namespace vk::gui{class Imgui;}
namespace vk::main{class Interface;}
namespace vk::structure{class Vulkan;}
namespace eng{class Node;}
namespace cam::gui{class Control;}
namespace dat::gui{class Control;}
namespace dyn::gui{class Control;}


namespace rnd::gui{

class Renderer
{
public:
  //Constructor / Destructor
  Renderer(rnd::Node* node_render);
  ~Renderer();

public:
  //Main function
  void run_panel();
  void design_panel();

  //Subfunction
  void engine_texture();
  void resize();

private:
  cam::gui::Control* cam_control;
  dat::gui::Control* dat_control;
  dyn::gui::Control* dyn_control;
  vk::gui::Imgui* vk_imgui;
  vk::main::Interface* vk_interface;
  vk::structure::Vulkan* vk_struct;

  std::string name;
  bool has_been_initialized;
};

}
