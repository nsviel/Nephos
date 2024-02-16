#pragma once

#include <Utility/Specific/common.h>

namespace gui{class Node;}
namespace k4n{class Node;}
namespace k4n::utils{class Transformation;}
namespace k4n::dev{class Swarm;}
namespace k4n::dev{class Sensor;}


namespace k4n::gui{

class Sensor
{
public:
  //Constructor / Destructor
  Sensor(k4n::Node* node_k4n);
  ~Sensor();

  //Main function
  void show_sensor(k4n::dev::Sensor* sensor);

  //Subfunction
  void show_sensor_info(k4n::dev::Sensor* sensor);
  void show_sensor_transfo(k4n::dev::Sensor* sensor);

private:
  k4n::Node* node_k4n;
  k4n::dev::Swarm* k4n_swarm;
  k4n::utils::Transformation* k4n_transfo;

  int item_width;
};

}
