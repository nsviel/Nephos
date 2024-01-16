#pragma once

#include <GUI/GUI_utility/Base/Namespace.h>
#include <Utility/Specific/common.h>
#include <Engine/Capture/K4N/Namespace.h>


namespace gui::kinect{

class Recorder
{
public:
  //Constructor / Destructor
  Recorder(k4n::Node* node_kinect);
  ~Recorder();

  //Main function
  void kinect_recorder();

  //Subfunction
  void recorder_path();

private:
  k4n::Node* node_kinect;
  k4n::dev::Swarm* k4a_swarm;
};

}
