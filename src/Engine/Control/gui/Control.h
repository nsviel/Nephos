#pragma once

#include <glm/glm.hpp>

namespace ctl{class Node;}
namespace ctl{class Structure;}
namespace ctl::gui{class Edition;}
namespace ctl::gui{class Navigation;}
namespace ctl::gui{class Player;}
namespace ctl::gui{class Render;}


namespace ctl::gui{

class Control
{
public:
  //Constructor / Destructor
  Control(itf::Node* node_interface);
  ~Control();

public:
  //Main function
  void run_control();

private:
  itf::Structure* itf_struct;
  itf::gui::Navigation* gui_navigation;
  itf::gui::Edition* gui_edition;
  itf::gui::Player* gui_player;
  itf::gui::Render* gui_render;
};

}
