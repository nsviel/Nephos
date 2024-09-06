#pragma once

#include <Kinect/src/Structure/Sensor.h>

namespace k4n{class Node;}
namespace k4n::playback{class Playback;}
namespace k4n::processing::cloud{class Data;}
namespace k4n::processing::image{class Data;}
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
  void manage_query(float ts_querry);
  void manage_gui();

public:
  k4n::playback::Playback* k4n_playback;
  k4n::processing::image::Data* k4n_image;
  k4n::processing::cloud::Data* k4n_cloud;
  k4n::gui::Playback* gui_playback;
  dyn::prc::cloud::Operation* dyn_ope_cloud;
  dat::sensor::Pool* thr_pool;
};

}
