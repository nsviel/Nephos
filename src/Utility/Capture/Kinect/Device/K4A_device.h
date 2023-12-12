#pragma once

#include <Utility/Capture/Kinect/Structure/Namespace.h>
#include <Utility/Capture/Kinect/Device/Configuration.h>
#include <Utility/Specific/common.h>

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
  void run_capture();
  void run_replay(string path);
  void stop_threads();

public:
  K4A_capture* k4a_capture;
  K4A_replay* k4a_replay;

  util::kinect::structure::Device device;
  util::kinect::structure::Synchro synchro;
  util::kinect::structure::File file;

  util::kinect::structure::Color color;
  util::kinect::structure::Depth depth;
  util::kinect::structure::Infrared ir;
};
