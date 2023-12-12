#pragma once

#include <GUI/GUI_utility/Base/Namespace.h>
#include <Utility/Specific/common.h>
#include <Engine/Capture/Kinect/Device/K4A_device.h>
#include <Engine/Capture/Kinect/Namespace.h>


namespace gui::kinect{

class Recorder
{
public:
  //Constructor / Destructor
  Recorder(util::kinect::Kinect* kinect);
  ~Recorder();

  //Main function
  void kinect_recorder();

private:
  util::kinect::Kinect* kinect;
};

}
