#pragma once

#include <Engine/Capture/K4A/Device/K4A_device.h>
#include <Utility/Specific/common.h>


namespace eng::kinect::data{

class Infrared
{
public:
  //Constructor / Destructor
  Infrared();
  ~Infrared();

public:
  //Main function
  std::vector<uint8_t> convert_ir_into_color(K4A_device* device);
  void find_ir_level(K4A_device* device);

private:

};

}
