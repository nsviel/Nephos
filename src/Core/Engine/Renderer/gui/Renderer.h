#pragma once

#include <string>

namespace rnd{class Node;}
namespace ctl::mode{class Navigation;}
namespace ctl::gui{class Control;}
namespace vk::gui{class Imgui;}
namespace vk{class Structure;}
namespace core{class Node;}


namespace rnd::gui{

class Renderer
{
public:
  //Constructor / Destructor
  Renderer(rnd::Node* node_interface);
  ~Renderer();

public:
  //Main function
  void run_panel();
  void design_panel();

  //Subfunction
  void engine_texture();
  void resize();

private:
  ctl::gui::Control* gui_control;
  ctl::mode::Navigation* ctl_navigation;
  vk::gui::Imgui* vk_imgui;
  vk::Structure* vk_struct;

  std::string name;
  bool has_been_initialized;
};

}
