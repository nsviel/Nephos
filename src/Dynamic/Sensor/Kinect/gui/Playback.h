#pragma once

#include <memory>

namespace k4n{class Node;}
namespace k4n{class Structure;}
namespace k4n::playback{class Sensor;}


namespace k4n::gui{

class Playback
{
public:
  //Constructor / Destructor
  Playback(k4n::Node* node_k4n);
  ~Playback();

  //Main function
  void show_parameter(k4n::playback::Sensor& sensor);

  //Subfunction
  void show_transformation_mode();
  void show_firmware_info(k4n::playback::Sensor& sensor);
  void show_info_device(k4n::playback::Sensor& sensor);
  void show_info_color(k4n::playback::Sensor& sensor);
  void show_info_depth(k4n::playback::Sensor& sensor);
  void show_info_synch(k4n::playback::Sensor& sensor);

private:
  k4n::Structure* k4n_struct;
  k4n::Node* node_k4n;
};

}
