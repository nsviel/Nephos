#ifndef K4A_INFRARED_H
#define K4A_INFRARED_H

#include <UTL_capture/UTL_kinect/K4A_device/K4A_device.h>
#include <UTL_specific/common.h>

class Struct_swarm;


class K4A_infrared
{
public:
  //Constructor / Destructor
  K4A_infrared(Struct_swarm* struct_swarm);
  ~K4A_infrared();

public:
  //Main function
  uint8_t* convert_ir_into_color(K4A_device* device);
  void find_ir_level(K4A_device* device);

private:
  Struct_swarm* struct_swarm;
};

#endif
