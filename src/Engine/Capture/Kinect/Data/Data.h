#pragma once

#include <Engine/Capture/Kinect/Device/K4A_device.h>
#include <Utility/Specific/common.h>


namespace eng::kinect::data{

class Data
{
public:
  //Constructor / Destructor
  Data();
  ~Data();

public:
  //Main function
  void find_data_from_capture(K4A_device* device, k4a::capture capture);

  //Subfunction
  void find_depth(K4A_device* k4a_device, k4a::capture capture);
  void find_color(K4A_device* k4a_device, k4a::capture capture);
  void find_color_from_depth(K4A_device* k4a_device, k4a::capture capture);
  void find_ir(K4A_device* k4a_device, k4a::capture capture);

private:
};

}
