#pragma once

#include <Utility/Specific/common.h>
#include <Engine/Capture/K4A/Namespace.h>

class GUI;
class K4A_swarm;


namespace gui::kinect{

class Capture
{
public:
  //Constructor / Destructor
  Capture(eng::kinect::Kinect* kinect);
  ~Capture();

  //Main function
  void kinect_configuration();

  //Subfunction
  void kinect_devices();
  void configuration_depth();
  void configuration_color();
  void configuration_device();
  void firmware_info();

private:
  eng::kinect::Kinect* kinect;
  K4A_swarm* k4a_swarm;

  int item_width;
};

}
