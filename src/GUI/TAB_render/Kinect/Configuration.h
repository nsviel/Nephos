#pragma once

#include <Utility/Specific/common.h>
#include <Engine/Capture/Kinect/Namespace.h>

class GUI;
class K4A_swarm;


namespace gui::kinect{

class Configuration
{
public:
  //Constructor / Destructor
  Configuration(util::kinect::Kinect* kinect);
  ~Configuration();

  //Main function
  void kinect_configuration();

  //Subfunction
  void kinect_devices();
  void configuration_device();
  void configuration_depth();
  void configuration_color();
  void configuration_general();
  void firmware_info();

private:
  util::kinect::Kinect* kinect;
  K4A_swarm* k4a_swarm;

  int item_width;
};

}
