#pragma once

#include <glm/glm.hpp>

namespace ctr{class Node;}
namespace ctr{class Structure;}
namespace ctr::mode{class Navigation;}


namespace ctr::gui{

class Navigation
{
public:
  //Constructor / Destructor
  Navigation(ctr::Node* node_control);
  ~Navigation();

public:
  //Main function
  void run_control();

  //Subfunction
  void control_keyboard();
  void control_mouse();
  void control_wheel();

private:
  ctr::Structure* ctr_struct;
  ctr::mode::Navigation* ctr_navigation;
};

}
