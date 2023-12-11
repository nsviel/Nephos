#pragma once

#include <UTL_specific/common.h>

class GUI;
class Kinect;
class K4A_swarm;


namespace gui::kinect{

class Configuration
{
public:
  //Constructor / Destructor
  Configuration(Kinect* kinect);
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
  Kinect* kinect;
  K4A_swarm* k4a_swarm;

  int item_width;
};

}
