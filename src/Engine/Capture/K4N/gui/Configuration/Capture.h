#pragma once

#include <Utility/Specific/common.h>
#include <Engine/Capture/K4N/Namespace.h>

class GUI;


namespace eng::k4n::gui{

class Capture
{
public:
  //Constructor / Destructor
  Capture(eng::k4n::Node* node_kinect);
  ~Capture();

  //Main function
  void show_sensor_configuration(eng::k4n::dev::Sensor* k4n_sensor);

  //Subfunction
  void kinect_devices();
  void configuration_depth();
  void configuration_color();
  void configuration_device();
  void firmware_info();

private:
  eng::k4n::Node* node_kinect;
  eng::k4n::dev::Swarm* k4n_swarm;

  int item_width;
};

}
