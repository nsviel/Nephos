#pragma once

#include <Utility/Specific/common.h>

namespace eng::k4n{class Node;}
namespace eng::k4n::dev{class Sensor;}
namespace eng::k4n::dev{class Swarm;}


namespace eng::k4n::gui{

class Playback
{
public:
  //Constructor / Destructor
  Playback(eng::k4n::Node* k4a_node);
  ~Playback();

  //Main function
  void show_sensor_configuration(eng::k4n::dev::Sensor* k4n_sensor);

  //Subfunction
  void show_info_device();
  void show_info_color();
  void show_info_depth();
  void show_info_synch();

private:
  eng::k4n::Node* k4a_node;
  eng::k4n::dev::Swarm* k4n_swarm;
};

}
