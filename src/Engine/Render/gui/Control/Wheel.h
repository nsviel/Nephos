#pragma once

#include <Utility/Specific/Common.h>

namespace rnd{class Node;}
namespace eng{class Node;}
namespace ope{class Operation;}
namespace dat{class Database;}
namespace cam{class Control;}

enum Wheel_mode{
  WHEEL_R_X = 0,
  WHEEL_R_Y = 1,
  WHEEL_R_Z = 2,
  WHEEL_CAM_Z = 3,
};


namespace rnd::gui{

class Wheel
{
public:
  //Constructor / Destructor
  Wheel(rnd::Node* node_render);
  ~Wheel();

public:
  //Main function
  void change_mode();
  void make_action(float direction);

  //Subfunction
  vector<const char*> get_vec_mode();

  inline int* get_mode(){return &mode;}

private:
  dat::Database* sce_database;
  cam::Control* cam_control;
  ope::Operation* ope_operation;

  int mode;
};

}
