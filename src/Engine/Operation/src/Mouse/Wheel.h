#pragma once

#include <Utility/Specific/common.h>

namespace eng{class Node;}
namespace eng::ope{class Operation;}
namespace eng::scene{class Scene;}
namespace eng::cam{class Control;}

enum Wheel_mode{
  WHEEL_R_X = 0,
  WHEEL_R_Y = 1,
  WHEEL_R_Z = 2,
  WHEEL_CAM_Z = 3,
};


namespace eng::ope{

class Wheel
{
public:
  //Constructor / Destructor
  Wheel(eng::Node* engine);
  ~Wheel();

public:
  //Main function


private:
  eng::scene::Scene* sce_scene;
  eng::cam::Control* cam_control;
  eng::ope::Operation* ope_operation;
};

}
