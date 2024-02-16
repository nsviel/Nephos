#pragma once

#include <Utility/Specific/common.h>

namespace gui{class Node;}
namespace k4n{class Node;}
namespace k4n::dev{class Sensor;}
namespace k4n::dev{class Swarm;}


namespace k4n::gui{

class Capture
{
public:
  //Constructor / Destructor
  Capture(k4n::Node* node_k4n);
  ~Capture();

  //Main function
  void show_sensor_configuration(k4n::dev::Sensor* sensor);

  //Subfunction
  void list_device(k4n::dev::Sensor* sensor);
  void configuration_depth(k4n::dev::Sensor* sensor);
  void configuration_color(k4n::dev::Sensor* sensor);
  void configuration_device(k4n::dev::Sensor* sensor);
  void firmware_info(k4n::dev::Sensor* sensor);

private:
  k4n::Node* node_k4n;
  k4n::dev::Swarm* k4n_swarm;

  int item_width;
};

}
