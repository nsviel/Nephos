#pragma once

#include <Utility/Capture/Kinect/Device/K4A_device.h>

#include <Utility/Specific/common.h>
#include <k4a/k4a.h>
#include <k4a/k4a.hpp>


namespace util::kinect::data{

class Data
{
public:
  //Constructor / Destructor
  Data();
  ~Data();

public:
  //Main function
  void find_data_from_capture(util::kinect::structure::Data* data, k4a::capture capture);

private:
};

}
