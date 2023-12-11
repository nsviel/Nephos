#pragma once

#include <Utility/Capture/Kinect/Device/K4A_device.h>
#include <Utility/Specific/common.h>


namespace util::kinect::data{

class Depth
{
public:
  //Constructor / Destructor
  Depth();
  ~Depth();

public:
  //Main function
  uint8_t* convert_depth_into_color(K4A_device* device);
  void find_depth_mode_range(K4A_device* device);

private:
};

}
