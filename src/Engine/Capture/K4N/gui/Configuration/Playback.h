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
  Playback(eng::k4n::Node* node_k4n);
  ~Playback();

  //Main function
  void show_sensor_configuration(eng::k4n::dev::Sensor* sensor);

  //Subfunction
  void show_info_device(eng::k4n::dev::Sensor* sensor);
  void show_info_color(eng::k4n::dev::Sensor* sensor);
  void show_info_depth(eng::k4n::dev::Sensor* sensor);
  void show_info_synch(eng::k4n::dev::Sensor* sensor);

private:
  eng::k4n::Node* node_k4n;
  eng::k4n::dev::Swarm* k4n_swarm;
};

}
