#pragma once

#include <Utility/Capture/Kinect/K4A_device/K4A_device.h>

#include <Utility/Specific/common.h>
#include <k4a/k4a.h>
#include <k4a/k4a.hpp>


class K4A_data
{
public:
  //Constructor / Destructor
  K4A_data();
  ~K4A_data();

public:
  //Main function
  void find_data_from_capture(util::kinect::structure::Struct_k4a_data* data, k4a::capture capture);

private:
};
