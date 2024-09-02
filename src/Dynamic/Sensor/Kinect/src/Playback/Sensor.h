#pragma once

#include <Kinect/src/Structure/Sensor.h>

namespace k4n{class Node;}
namespace k4n{class Graph;}
namespace k4n::playback{class Configuration;}
namespace k4n::playback{class Playback;}
namespace k4n::gui{class Playback;}
namespace utl::base{class Path;}
namespace dat::elm{class Sensor;}


namespace k4n::playback{

class Sensor : public k4n::base::Sensor
{
public:
  //Constructor / Destructor
  Sensor(k4n::Node* node_k4n, utl::base::Path path);
  ~Sensor();

public:
  //Main function
  void thread_init();
  void thread_loop();
  void thread_end();

  //Subfunction
  void manage_capture();
  void manage_query(float ts_querry);
  void manage_gui();

public:
  k4n::Graph* k4n_graph;
  k4n::playback::Configuration* k4n_config;
  k4n::playback::Playback* k4n_playback;
  k4n::gui::Playback* gui_playback;
  dat::elm::Sensor* dat_sensor;
};


}
