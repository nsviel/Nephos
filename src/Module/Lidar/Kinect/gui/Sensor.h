#pragma once

#include <Utility/Specific/Common.h>

namespace gui{class Node;}
namespace k4n{class Node;}
namespace k4n::dev{class Sensor;}
namespace k4n::gui{class Playback;}


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
  void show_firmware_info(k4n::dev::Sensor* sensor);
  void show_sensor_recorder(k4n::dev::Sensor* sensor);

private:
  k4n::Node* node_k4n;
  k4n::gui::Playback* gui_playback;

  int item_width;
};

}
