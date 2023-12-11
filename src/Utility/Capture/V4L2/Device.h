#pragma once

#include <Utility/Specific/common.h>
#include <libudev.h>


struct Struct_video_device{
  //---------------------------

  string name;
  string node;

  //---------------------------
};

namespace util::v4l2{

class Device
{
public:
  //Constructor / Destructor
  Device();
  ~Device();

public:
  //Main function
  void find_video_devices();

private:
  vector<Struct_video_device> vec_video_device;
};

}
