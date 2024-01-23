#pragma once

#include <Utility/Base/GUI/Panel.h>
#include <Utility/Specific/common.h>
#include <Engine/Capture/K4N/Namespace.h>


namespace gui::kinect{

class Playback
{
public:
  //Constructor / Destructor
  Playback(eng::k4n::Node* node_kinect);
  ~Playback();

  //Main function
  void show_sensor_configuration(eng::k4n::dev::Sensor* k4n_sensor);

  //Subfunction
  void show_info_device();
  void show_info_color();
  void show_info_depth();
  void show_info_synch();

private:
  eng::k4n::Node* node_kinect;
  eng::k4n::dev::Swarm* k4n_swarm;
};

}
