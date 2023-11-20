#ifndef UTL_DEVICE_H
#define UTL_DEVICE_H

#include <UTL_specific/common.h>
#include <UTL_struct/Struct_video_device.h>
#include <libudev.h>


class UTL_device
{
public:
  //Constructor / Destructor
  UTL_device();
  ~UTL_device();

public:
  //Main function
  void find_video_devices();

  vector<Struct_video_device> get_vec_video_device(){return vec_video_device;};

private:
  vector<Struct_video_device> vec_video_device;
};

#endif
