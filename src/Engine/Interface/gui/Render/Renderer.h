#pragma once

#include <string>

namespace itf{class Node;}
namespace itf::control{class Navigation;}
namespace vk::gui{class Imgui;}
namespace vk{class Structure;}
namespace eng{class Node;}
namespace itf::gui{class Control;}


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
  itf::gui::Control* gui_control;
  itf::control::Navigation* ctl_navigation;
  vk::gui::Imgui* vk_imgui;
  vk::Structure* vk_struct;

  std::string name;
  bool has_been_initialized;
};

}
