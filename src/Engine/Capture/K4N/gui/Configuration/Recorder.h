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
  Recorder(eng::k4n::Node* k4a_node);
  ~Recorder();

  //Main function
  void show_sensor_recorder();

  //Subfunction
  void recorder_path();

private:
  eng::k4n::Node* k4a_node;
  eng::k4n::dev::Swarm* k4n_swarm;
};

}
