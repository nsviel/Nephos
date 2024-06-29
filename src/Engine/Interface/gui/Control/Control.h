#pragma once

#include <glm/glm.hpp>

namespace itf{class Node;}
namespace itf{class Structure;}
namespace itf::gui{class Edition;}
namespace itf::gui{class Navigation;}
namespace itf::gui{class Player;}


namespace itf::gui{

class Control
{
public:
  //Constructor / Destructor
  Control(itf::Node* node_interface);
  ~Control();

public:
  //Main function
  void run_control(glm::vec2 center);

private:
  itf::Structure* itf_struct;
  itf::gui::Navigation* gui_navigation;
  itf::gui::Edition* gui_edition;
  itf::gui::Player* gui_player;
};

}
