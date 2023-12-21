#pragma once

#include <Engine/Capture/K4A/Structure/Namespace.h>
#include <Utility/Specific/common.h>
#include <Engine/Capture/K4A/Device/K4A_device.h>
#include <k4arecord/playback.hpp>


namespace eng::kinect{

class Operation
{
public:
  //Constructor / Destructor
  Operation();
  ~Operation();

public:
  //Main function
  void make_colorization(eng::kinect::structure::Cloud* cloud, vector<vec4>& vec_rgba);

private:

};

}
