#pragma once

#include <Utility/Capture/Kinect/Device/K4A_device.h>
#include <Utility/Specific/common.h>


namespace util::kinect::data{

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
  void find_color(K4A_device* k4a_device, k4a::capture capture);
  void find_depth(K4A_device* k4a_device, k4a::capture capture);
  void find_ir(K4A_device* k4a_device, k4a::capture capture);

private:
};

}
