#pragma once

#include <glm/glm.hpp>

namespace ctr{class Node;}
namespace ctr{class Structure;}
namespace ctr::gui{class Edition;}
namespace ctr::gui{class Navigation;}
namespace ctr::gui{class Player;}
namespace ctr::gui{class Render;}


namespace ctr::gui{

class Control
{
public:
  //Constructor / Destructor
  Control(ctr::Node* node_control);
  ~Control();

public:
  //Main function
  void run_control();

private:
  ctr::Structure* ctr_struct;
  ctr::gui::Navigation* gui_navigation;
  ctr::gui::Edition* gui_edition;
  ctr::gui::Player* gui_player;
  ctr::gui::Render* gui_render;
};

}
