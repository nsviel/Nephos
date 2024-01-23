#pragma once

#include <Utility/Specific/common.h>
#include <Engine/Capture/K4N/Namespace.h>

class GUI;


namespace gui::kinect{

class Sensor
{
public:
  //Constructor / Destructor
  Sensor(eng::k4n::Node* node_kinect);
  ~Sensor();

  //Main function
  void show_sensor(eng::k4n::dev::Sensor* sensor);

  //Subfunction
  void show_sensor_info(eng::k4n::dev::Sensor* sensor);
  void show_sensor_transfo(eng::k4n::dev::Sensor* sensor);

private:
  eng::k4n::Node* node_kinect;
  eng::k4n::dev::Swarm* k4n_swarm;
  eng::k4n::utils::Transformation* k4n_transfo;

  int item_width;
};

}
