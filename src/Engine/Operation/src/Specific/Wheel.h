#pragma once

#include <Utility/Specific/Common.h>

namespace eng{class Node;}
namespace ope{class Node;}
namespace ope{class Operation;}
namespace eng::scene{class Database;}
namespace eng::cam{class Control;}

enum Wheel_mode{
  WHEEL_R_X = 0,
  WHEEL_R_Y = 1,
  WHEEL_R_Z = 2,
  WHEEL_CAM_Z = 3,
};


namespace ope{

class Wheel
{
public:
  //Constructor / Destructor
  Wheel(ope::Node* node_operation);
  ~Wheel();

public:
  //Main function
  void change_mode();
  void make_action(float direction);

  //Subfunction
  vector<const char*> get_vec_mode();

  inline int* get_mode(){return &mode;}

private:
  eng::scene::Database* sce_database;
  eng::cam::Control* cam_control;
  ope::Operation* ope_operation;

  int mode;
};

}
