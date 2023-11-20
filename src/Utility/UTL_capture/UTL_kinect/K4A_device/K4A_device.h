#ifndef K4A_DEVICE_H
#define K4A_DEVICE_H

#include <UTL_capture/UTL_kinect/K4A_struct/Struct_k4a_device.h>

#include <UTL_specific/common.h>
#include <k4a/k4a.h>
#include <k4a/k4a.hpp>

class Struct_kinect;


class K4A_device
{
public:
  //Constructor / Destructor
  K4A_device(Struct_kinect* struct_kinect);
  ~K4A_device();

public:
  //Main function
  void refresh_device_list();

private:
  Struct_kinect* struct_kinect;
};

#endif
