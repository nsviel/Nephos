#pragma once

#include <Utility/Capture/Kinect/K4A_device/K4A_device.h>
#include <Utility/Capture/Kinect/Base/Namespace.h>
#include <Utility/Specific/common.h>


namespace util::kinect::data{

class Infrared
{
public:
  //Constructor / Destructor
  Infrared();
  ~Infrared();

public:
  //Main function
  uint8_t* convert_ir_into_color(K4A_device* device);
  void find_ir_level(K4A_device* device);

private:

};

}
