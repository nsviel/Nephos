#pragma once

#include <glm/glm.hpp>
#include <vector>

namespace ctl{class Node;}
namespace ctl{class Structure;}
namespace eng{class Node;}
namespace ope{class Operation;}
namespace ope::attribut{class Location;}
namespace dat::graph{class Selection;}


namespace ctl{

class Wheel
{
public:
  //Constructor / Destructor
  Wheel(itf::Node* node_interface);
  ~Wheel();

public:
  //Main function
  void make_action(float value);

  //Subfunction
  void change_mode();
  std::vector<const char*> get_vec_mode();

private:
  itf::Structure* itf_struct;
  dat::graph::Selection* dat_selection;
  eng::Node* node_engine;
  ope::Operation* ope_operation;
  ope::attribut::Location* ope_location;
};

}
