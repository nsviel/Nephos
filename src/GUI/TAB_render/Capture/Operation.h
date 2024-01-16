#pragma once

#include <Utility/Specific/common.h>
#include <Engine/Capture/K4N/Namespace.h>

class GUI;


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
  k4n::dev::Swarm* k4a_swarm;

  int item_width;
};

}
