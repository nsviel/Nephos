#pragma once

#include <glm/glm.hpp>
#include <vector>

namespace dat{class Node;}
namespace eng{class Node;}
namespace ope{class Operation;}
namespace dat{class Graph;}

enum Wheel_mode{
  WHEEL_R_X = 0,
  WHEEL_R_Y = 1,
  WHEEL_R_Z = 2,
  WHEEL_CAM_Z = 3,
};


namespace dat::gui{

class Wheel
{
public:
  //Constructor / Destructor
  Wheel(dat::Node* node_data);
  ~Wheel();

public:
  //Main function
  void change_mode();
  void make_action(float direction);

  //Subfunction
  std::vector<const char*> get_vec_mode();

  inline int* get_mode(){return &mode;}

private:
  dat::Graph* dat_graph;
  eng::Node* node_engine;
  ope::Operation* ope_operation;

  int mode;
};

}
