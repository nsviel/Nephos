#pragma once

#include <glm/glm.hpp>
#include <vector>

namespace ctl{class Node;}
namespace ctl{class Structure;}
namespace core{class Node;}
namespace ope{class Operation;}
namespace ope::attribut{class Location;}
namespace dat::graph{class Selection;}


namespace ctl{

class Wheel
{
public:
  //Constructor / Destructor
  Wheel(ctl::Node* node_control);
  ~Wheel();

public:
  //Main function
  void make_action(float value);

  //Subfunction
  void change_mode();
  std::vector<const char*> get_vec_mode();

private:
  ctl::Structure* ctl_struct;
  dat::graph::Selection* dat_selection;
  core::Node* node_core;
  ope::Operation* ope_operation;
  ope::attribut::Location* ope_location;
};

}
