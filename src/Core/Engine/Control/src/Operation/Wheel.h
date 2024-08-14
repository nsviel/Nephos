#pragma once

#include <glm/glm.hpp>
#include <vector>

namespace ctr{class Node;}
namespace ctr{class Structure;}
namespace cam{class Control;}
namespace ope{class Operation;}
namespace ope::attribut{class Location;}
namespace dat::graph{class Selection;}


namespace ctr{

class Wheel
{
public:
  //Constructor / Destructor
  Wheel(ctr::Node* node_control);
  ~Wheel();

public:
  //Main function
  void make_action(float value);

  //Subfunction
  void change_mode();
  std::vector<const char*> get_vec_mode();

private:
  ctr::Structure* ctr_struct;
  dat::graph::Selection* dat_selection;
  cam::Control* cam_control;
  ope::Operation* ope_operation;
  ope::attribut::Location* ope_location;
};

}
