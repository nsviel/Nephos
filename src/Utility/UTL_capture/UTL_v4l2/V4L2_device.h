#pragma once

#include <Utility/UTL_specific/common.h>
#include <libudev.h>


struct Struct_video_device{
  //---------------------------

  string name;
  string node;

  //---------------------------
};

class V4L2_device
{
public:
  //Constructor / Destructor
  V4L2_device();
  ~V4L2_device();

public:
  //Main function
  void find_video_devices();

private:
  vector<Struct_video_device> vec_video_device;
};
