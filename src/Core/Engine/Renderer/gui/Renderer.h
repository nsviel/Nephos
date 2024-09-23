#pragma once

#include <string>

namespace rnd{class Node;}
namespace ctr::mode{class Navigation;}
namespace ctr::gui{class Control;}
namespace vk::interface{class Render;}
namespace vk{class Structure;}
namespace core{class Node;}


namespace rnd::gui{

class Renderer
{
public:
  //Constructor / Destructor
  Renderer(rnd::Node* node_renderer);
  ~Renderer();

public:
  //Main function
  void run_panel();
  void design_panel();

  //Subfunction
  void engine_texture();
  void resize();

private:
  ctr::gui::Control* gui_control;
  ctr::mode::Navigation* ctr_navigation;
  vk::interface::Render* vk_render;
  vk::Structure* vk_struct;

  std::string name;
  bool has_been_initialized;
};

}
