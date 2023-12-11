#pragma once

#include <Utility/Capture/UTL_kinect/K4A_device/K4A_device.h>
#include <Utility/Specific/common.h>

class Struct_k4a_swarm;


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
