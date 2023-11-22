#ifndef K4A_INFRARED_H
#define K4A_INFRARED_H

#include <UTL_capture/UTL_kinect/K4A_struct/Struct_k4a_device.h>
#include <UTL_specific/common.h>

class Struct_kinect;


class K4A_infrared
{
public:
  //Constructor / Destructor
  K4A_infrared();
  ~K4A_infrared();

public:
  //Main function
  uint8_t* convert_ir_into_color(Struct_k4a_device* device);
  void find_ir_level(Struct_k4a_device* device);

private:
  Struct_kinect* struct_kinect;
};

#endif
