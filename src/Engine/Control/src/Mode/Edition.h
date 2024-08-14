#pragma once

#include <glm/glm.hpp>
#include <vector>

namespace ctl{class Node;}
namespace ctl{class Structure;}
namespace dat::graph{class Selection;}
namespace dat::element{class Set;}
namespace ope{class Operation;}


namespace ctl::mode{

class Edition
{
public:
  //Constructor / Destructor
  Edition(ctl::Node* node_control);
  ~Edition();

public:
  //Main function
  void element_forward();
  void element_backward();
  void element_left();
  void element_right();
  void element_down();
  void element_up();
  void element_zoom(float value);

  //Subfunction
  void select_next();
  void remove_current();

private:
  ctl::Structure* ctl_struct;
  dat::graph::Selection* dat_selection;
  dat::element::Set* dat_set;
  ope::Operation* ope_operation;
};

}
