#pragma once

#include <string>

namespace itf{class Node;}
namespace itf::control{class Navigation;}
namespace vk::gui{class Imgui;}
namespace vk{class Structure;}
namespace eng{class Node;}
namespace itf::gui{class Navigation;}
namespace itf::gui{class Edition;}
namespace itf::gui{class Player;}


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
  itf::gui::Navigation* gui_navigation;
  itf::control::Navigation* itf_navigation;
  itf::gui::Edition* gui_edition;
  itf::gui::Player* itf_player;
  vk::gui::Imgui* vk_imgui;
  vk::Structure* vk_struct;

  std::string name;
  bool has_been_initialized;
};

}
