#pragma once

#include <GUI/GUI_utility/Base/Namespace.h>
#include <Utility/Specific/common.h>
#include <Engine/Capture/K4A/Device/K4A_device.h>
#include <Engine/Capture/K4A/Namespace.h>

class K4A_swarm;


namespace gui::kinect{

class Recorder
{
public:
  //Constructor / Destructor
  Recorder(eng::kinect::Kinect* kinect);
  ~Recorder();

  //Main function
  void kinect_recorder();

  //Subfunction
  void recorder_path();

private:
  eng::kinect::Kinect* kinect;
  K4A_swarm* k4a_swarm;
};

}
