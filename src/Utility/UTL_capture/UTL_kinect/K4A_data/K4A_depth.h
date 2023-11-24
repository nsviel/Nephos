#ifndef K4A_DEPTH_H
#define K4A_DEPTH_H

#include <UTL_capture/UTL_kinect/K4A_device/K4A_device.h>
#include <UTL_specific/common.h>

class Struct_kinect;


class K4A_depth
{
public:
  //Constructor / Destructor
  K4A_depth(Struct_kinect* struct_kinect);
  ~K4A_depth();

public:
  //Main function
  uint8_t* convert_depth_into_color(K4A_device* device);
  void find_depth_mode_range(K4A_device* device);

private:
  Struct_kinect* struct_kinect;
};

#endif
