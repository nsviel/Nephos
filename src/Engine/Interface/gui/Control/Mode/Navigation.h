#pragma once

#include <glm/glm.hpp>

namespace itf{class Node;}
namespace itf{class Structure;}
namespace itf::control{class Navigation;}


namespace itf::gui{

class Navigation
{
public:
  //Constructor / Destructor
  Navigation(itf::Node* node_interface);
  ~Navigation();

public:
  //Main function
  void run_control(glm::vec2 center);

  //Subfunction
  void control_keyboard();
  void control_mouse(glm::vec2 center);
  void control_wheel();

private:
  itf::Structure* itf_struct;
  itf::control::Navigation* itf_navigation;
};

}
