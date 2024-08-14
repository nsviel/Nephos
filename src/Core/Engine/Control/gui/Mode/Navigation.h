#pragma once

#include <glm/glm.hpp>

namespace ctl{class Node;}
namespace ctl{class Structure;}
namespace ctl::mode{class Navigation;}


namespace ctl::gui{

class Navigation
{
public:
  //Constructor / Destructor
  Navigation(ctl::Node* node_control);
  ~Navigation();

public:
  //Main function
  void run_control();

  //Subfunction
  void control_keyboard();
  void control_mouse();
  void control_wheel();

private:
  ctl::Structure* ctl_struct;
  ctl::mode::Navigation* ctl_navigation;
};

}
