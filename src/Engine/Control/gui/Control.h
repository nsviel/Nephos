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
  Control(ctl::Node* node_control);
  ~Control();

public:
  //Main function
  void run_control();

private:
  ctl::Structure* ctl_struct;
  ctl::gui::Navigation* gui_navigation;
  ctl::gui::Edition* gui_edition;
  ctl::gui::Player* gui_player;
  ctl::gui::Render* gui_render;
};

}
