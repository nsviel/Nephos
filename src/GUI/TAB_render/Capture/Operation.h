#pragma once

#include <Utility/Specific/common.h>
#include <Engine/Capture/K4N/Namespace.h>

class GUI;
class K4A_swarm;


namespace gui::kinect{

class Operation
{
public:
  //Constructor / Destructor
  Operation(k4n::Node* node_kinect);
  ~Operation();

  //Main function
  void kinect_operation();

  //Subfunction
  void colorization();

private:
  k4n::Node* node_kinect;
  K4A_swarm* k4a_swarm;

  int item_width;
};

}
