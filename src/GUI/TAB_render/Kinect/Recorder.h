#pragma once

#include <GUI/GUI_utility/Base/Namespace.h>
#include <Utility/Specific/common.h>
#include <Engine/Capture/Kinect/Device/K4A_device.h>
#include <Engine/Capture/Kinect/Namespace.h>

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

private:
  eng::kinect::Kinect* kinect;
  K4A_swarm* k4a_swarm;
};

}
