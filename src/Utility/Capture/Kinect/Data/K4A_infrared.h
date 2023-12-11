#pragma once

#include <Utility/Capture/Kinect/K4A_device/K4A_device.h>
#include <Utility/Capture/Kinect/K4A_struct/Namespace.h>
#include <Utility/Specific/common.h>


namespace util::kinect::data{

class K4A_infrared
{
public:
  //Constructor / Destructor
  K4A_infrared();
  ~K4A_infrared();

public:
  //Main function
  uint8_t* convert_ir_into_color(K4A_device* device);
  void find_ir_level(K4A_device* device);

private:

};

}
