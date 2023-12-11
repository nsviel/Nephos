#pragma once

#include <GUI/GUI_utility/Base/Namespace.h>
#include <Utility/Specific/common.h>
#include <Utility/Capture/UTL_kinect/K4A_device/K4A_device.h>
#include <Utility/Capture/UTL_kinect/Namespace.h>


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
