#pragma once

#include <Utility/Capture/UTL_kinect/K4A_device/K4A_device.h>
#include <Utility/Specific/common.h>

class Struct_k4a_swarm;


class K4A_depth
{
public:
  //Constructor / Destructor
  K4A_depth();
  ~K4A_depth();

public:
  //Main function
  uint8_t* convert_depth_into_color(K4A_device* device);
  void find_depth_mode_range(K4A_device* device);

private:
};
