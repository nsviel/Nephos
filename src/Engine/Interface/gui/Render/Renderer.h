#pragma once

#include <string>

namespace itf{class Node;}
namespace vk::gui{class Imgui;}
namespace vk::main{class Interface;}
namespace vk{class Structure;}
namespace eng{class Node;}
namespace cam::gui{class Control;}
namespace dat::gui{class Control;}
namespace dyn::gui{class Control;}


namespace itf::gui{

class Renderer
{
public:
  //Constructor / Destructor
  Renderer(itf::Node* node_interface);
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
  vk::Structure* vk_struct;

  std::string name;
  bool has_been_initialized;
};

}
