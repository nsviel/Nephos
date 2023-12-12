#pragma once

#include <Utility/Capture/Kinect/Device/K4A_device.h>
#include <Utility/Specific/common.h>


namespace util::kinect::data{

class Cloud
{
public:
  //Constructor / Destructor
  Cloud();
  ~Cloud();

public:
  //Main function
  void convert_into_cloud(K4A_device* k4a_device);

private:

};

}
