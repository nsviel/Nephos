#pragma once

#include <Kinect/src/Structure/Sensor.h>
#include <Utility/Specific/Common.h>

namespace k4n{class Node;}
namespace k4n::processing{class Image;}
namespace k4n::utils{class Configuration;}
namespace k4n::gui{class Playback;}


namespace k4n::playback{

class Sensor : public k4n::structure::Sensor
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
  void info();
  k4a::capture* manage_new_capture();
  void manage_old_capture(k4a::capture* capture);
  void manage_pause();
  void manage_query(float ts_querry);

public:
  k4n::processing::Image* k4n_image;
  k4n::utils::Configuration* k4n_config;
  k4n::gui::Playback* gui_playback;

  k4a::playback playback;
};


}
