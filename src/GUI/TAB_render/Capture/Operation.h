#pragma once

#include <Utility/Specific/common.h>
#include <Engine/Capture/K4A/Namespace.h>

class GUI;
class K4A_swarm;


namespace gui::kinect{

class Operation
{
public:
  //Constructor / Destructor
  Operation(eng::kinect::Kinect* kinect);
  ~Operation();

  //Main function
  void kinect_operation();

  //Subfunction
  void colorization();

private:
  eng::kinect::Kinect* kinect;
  K4A_swarm* k4a_swarm;

  int item_width;
};

}
