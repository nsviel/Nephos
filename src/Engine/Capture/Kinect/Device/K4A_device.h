#pragma once

#include <Engine/Capture/Kinect/Structure/Namespace.h>
#include <Engine/Capture/Kinect/Device/Configuration.h>
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

  eng::kinect::structure::Device device;
  eng::kinect::structure::Synchro synchro;
  eng::kinect::structure::File file;

  eng::kinect::structure::Color color;
  eng::kinect::structure::Depth depth;
  eng::kinect::structure::Infrared ir;
};
