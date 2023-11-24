#ifndef K4A_DEVICE_H
#define K4A_DEVICE_H

#include <UTL_capture/UTL_kinect/K4A_struct/Struct_k4a_config.h>
#include <UTL_capture/UTL_kinect/K4A_struct/Struct_k4a_color.h>
#include <UTL_capture/UTL_kinect/K4A_struct/Struct_k4a_depth.h>
#include <UTL_capture/UTL_kinect/K4A_struct/Struct_k4a_infrared.h>
#include <UTL_capture/UTL_kinect/K4A_struct/Struct_k4a_data.h>
#include <UTL_capture/UTL_kinect/K4A_struct/Struct_k4a_info.h>

#include <UTL_specific/common.h>
#include <k4a/k4a.hpp>
#include <string>

class Struct_k4a_swarm;
class K4A_capture;
class K4A_replay;


class K4A_device
{
public:
  //Constructor / Destructor
  K4A_device();
  ~K4A_device();

public:
  //Main function


//private:
  K4A_capture* k4a_capture;
  K4A_replay* k4a_replay;

  Struct_k4a_config config;
  Struct_k4a_color color;
  Struct_k4a_depth depth;
  Struct_k4a_infrared ir;
  Struct_k4a_data data;
  Struct_k4a_info info;

  k4a::device* device;
  std::string serial_number;
  float temperature = 0;
  bool is_virtual;
  int index;
};

#endif
