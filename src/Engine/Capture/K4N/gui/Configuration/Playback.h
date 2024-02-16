#pragma once

#include <Utility/Specific/common.h>

namespace k4n{class Node;}
namespace k4n::dev{class Sensor;}
namespace k4n::dev{class Swarm;}


namespace k4n::gui{

class Playback
{
public:
  //Constructor / Destructor
  Playback(k4n::Node* node_k4n);
  ~Playback();

  //Main function
  void show_sensor_configuration(k4n::dev::Sensor* sensor);

  //Subfunction
  void show_info_device(k4n::dev::Sensor* sensor);
  void show_info_color(k4n::dev::Sensor* sensor);
  void show_info_depth(k4n::dev::Sensor* sensor);
  void show_info_synch(k4n::dev::Sensor* sensor);

private:
  k4n::Node* node_k4n;
  k4n::dev::Swarm* k4n_swarm;
};

}
