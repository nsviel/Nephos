#pragma once

#include <Utility/Specific/common.h>

namespace gui{class Node;}
namespace eng::k4n{class Node;}
namespace eng::k4n::dev{class Sensor;}
namespace eng::k4n::dev{class Swarm;}


namespace eng::k4n::gui{

class Capture
{
public:
  //Constructor / Destructor
  Capture(eng::k4n::Node* node_k4n);
  ~Capture();

  //Main function
  void show_sensor_configuration(eng::k4n::dev::Sensor* sensor);

  //Subfunction
  void list_device(eng::k4n::dev::Sensor* sensor);
  void configuration_depth(eng::k4n::dev::Sensor* sensor);
  void configuration_color(eng::k4n::dev::Sensor* sensor);
  void configuration_device(eng::k4n::dev::Sensor* sensor);
  void firmware_info(eng::k4n::dev::Sensor* sensor);

private:
  eng::k4n::Node* node_k4n;
  eng::k4n::dev::Swarm* k4n_swarm;

  int item_width;
};

}
