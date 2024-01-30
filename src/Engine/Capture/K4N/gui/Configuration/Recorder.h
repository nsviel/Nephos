#pragma once

#include <Utility/Specific/common.h>

namespace eng::k4n{class Node;}
namespace eng::k4n::dev{class Sensor;}
namespace eng::k4n::dev{class Swarm;}


namespace eng::k4n::gui{

class Recorder
{
public:
  //Constructor / Destructor
  Recorder(eng::k4n::Node* node_k4n);
  ~Recorder();

  //Main function
  void show_sensor_recorder(eng::k4n::dev::Sensor* sensor);

  //Subfunction
  void recorder_path(eng::k4n::dev::Sensor* sensor);

private:
  eng::k4n::Node* node_k4n;
  eng::k4n::dev::Swarm* k4n_swarm;
};

}
