#pragma once

#include <Utility/Specific/Common.h>

namespace k4n{class Node;}
namespace k4n::dev{class Device;}
namespace k4n::dev{class Master;}
namespace k4n::dev{class Swarm;}


namespace k4n::gui{

class Playback
{
public:
  //Constructor / Destructor
  Playback(k4n::Node* node_k4n);
  ~Playback();

  //Main function
  void show_master_playback(k4n::dev::Master* master);
  void show_sensor_configuration(k4n::dev::Device* sensor);

  //Subfunction
  void show_info_device(k4n::dev::Device* sensor);
  void show_info_color(k4n::dev::Device* sensor);
  void show_info_depth(k4n::dev::Device* sensor);
  void show_info_synch(k4n::dev::Device* sensor);

private:
  k4n::Node* node_k4n;
  k4n::dev::Swarm* k4n_swarm;
};

}
