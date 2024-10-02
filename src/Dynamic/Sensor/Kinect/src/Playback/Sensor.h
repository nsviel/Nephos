#pragma once

#include <Kinect/src/Structure/Sensor.h>

namespace k4n{class Node;}
namespace k4n::playback{class Playback;}
namespace k4n::data{class Cloud;}
namespace k4n::data{class Image;}
namespace k4n::gui{class Playback;}
namespace utl::base{class Path;}
namespace dyn::prc::cloud{class Operation;}
namespace dat::sensor{class Pool;}


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
  void query(float ts_querry);
  void gui_config();
  void gui_info();

public:
  k4n::playback::Playback* k4n_playback;
  k4n::data::Image* k4n_image;
  k4n::data::Cloud* k4n_cloud;
  k4n::gui::Playback* gui_playback;
  dyn::prc::cloud::Operation* dyn_operation;
  dat::sensor::Pool* thr_pool;
};

}
