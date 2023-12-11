#pragma once

#include <Utility/Capture/UTL_kinect/K4A_struct/Struct_k4a_config.h>
#include <Utility/Capture/UTL_kinect/K4A_struct/Struct_k4a_color.h>
#include <Utility/Capture/UTL_kinect/K4A_struct/Struct_k4a_depth.h>
#include <Utility/Capture/UTL_kinect/K4A_struct/Struct_k4a_infrared.h>
#include <Utility/Capture/UTL_kinect/K4A_struct/Struct_k4a_data.h>
#include <Utility/Capture/UTL_kinect/K4A_struct/Struct_k4a_info.h>

#include <Utility/Specific/common.h>
#include <k4a/k4a.hpp>
#include <string>

class Struct_k4a_swarm;
class K4A_capture;
class K4A_replay;
class K4A_configuration;


class K4A_device
{
public:
  //Constructor / Destructor
  K4A_device();
  ~K4A_device();

public:
  //Main function
  void run_capture();
  void run_replay(string path);
  void stop_threads();

public:
  K4A_capture* k4a_capture;
  K4A_replay* k4a_replay;
  K4A_configuration* k4a_configuration;

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
