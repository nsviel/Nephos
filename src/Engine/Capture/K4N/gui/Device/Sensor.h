#pragma once

#include <Utility/Specific/common.h>

namespace gui{class Node;}
namespace eng::k4n{class Node;}
namespace eng::k4n::utils{class Transformation;}
namespace eng::k4n::dev{class Swarm;}
namespace eng::k4n::dev{class Sensor;}


namespace eng::k4n::gui{

class Sensor
{
public:
  //Constructor / Destructor
  Sensor(eng::k4n::Node* k4a_node);
  ~Sensor();

  //Main function
  void show_sensor(eng::k4n::dev::Sensor* sensor);

  //Subfunction
  void show_sensor_info(eng::k4n::dev::Sensor* sensor);
  void show_sensor_transfo(eng::k4n::dev::Sensor* sensor);

private:
  eng::k4n::Node* k4a_node;
  eng::k4n::dev::Swarm* k4n_swarm;
  eng::k4n::utils::Transformation* k4n_transfo;

  int item_width;
};

}
