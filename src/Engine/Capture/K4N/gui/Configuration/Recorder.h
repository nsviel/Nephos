#pragma once

#include <Utility/Specific/common.h>

namespace k4n{class Node;}
namespace k4n::dev{class Sensor;}
namespace k4n::dev{class Swarm;}


namespace k4n::gui{

class Recorder
{
public:
  //Constructor / Destructor
  Recorder(k4n::Node* node_k4n);
  ~Recorder();

  //Main function
  void show_sensor_recorder(k4n::dev::Sensor* sensor);

  //Subfunction
  void recorder_path(k4n::dev::Sensor* sensor);

private:
  k4n::Node* node_k4n;
  k4n::dev::Swarm* k4n_swarm;
};

}
