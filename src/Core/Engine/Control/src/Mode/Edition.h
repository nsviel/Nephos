#pragma once

#include <glm/glm.hpp>
#include <vector>

namespace ctr{class Node;}
namespace ctr{class Structure;}
namespace dat::gph{class Selection;}
namespace dat::gph{class Element;}
namespace eng::trf{class Operation;}


namespace ctr::mode{

class Edition
{
public:
  //Constructor / Destructor
  Edition(ctr::Node* node_control);
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
  ctr::Structure* ctr_struct;
  dat::gph::Selection* gph_selection;
  dat::gph::Element* gph_element;
  eng::trf::Operation* trf_operation;
};

}
