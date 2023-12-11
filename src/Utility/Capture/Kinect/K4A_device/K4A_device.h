#pragma once

#include <Utility/Capture/Kinect/Base/Namespace.h>

#include <Utility/Specific/common.h>
#include <k4a/k4a.hpp>
#include <string>

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

  util::kinect::structure::Config config;
  util::kinect::structure::Color color;
  util::kinect::structure::Depth depth;
  util::kinect::structure::Infrared ir;
  util::kinect::structure::Data data;
  util::kinect::structure::Info info;

  k4a::device* device;
  std::string serial_number;
  float temperature = 0;
  bool is_virtual;
  int index;
};
