#pragma once

#include <Kinect/src/Structure/Sensor.h>
#include <Utility/Specific/Common.h>

namespace eng{class Node;}
namespace k4n{class Node;}
namespace k4n::dev{class Sensor;}
namespace k4n::gui{class Playback;}
namespace k4n::processing{class Data;}
namespace k4n::processing{class Image;}
namespace k4n::utils{class Configuration;}
namespace k4n::structure{class K4N;}
namespace k4n::synchro{class Configuration;}


namespace k4n::playback{

class Sensor : public k4n::dev::Sensor
{
public:
  //Constructor / Destructor
  Sensor(k4n::Node* node_k4n, utl::base::Path path);
  ~Sensor();

public:
  //Main function
  void info();
  void thread_init();
  void thread_loop();
  void thread_end();

  //Subfunction
  k4a::capture* manage_new_capture();
  void manage_old_capture(k4a::capture* capture);
  void manage_pause();
  void manage_query(float ts_querry);

public:
  k4a::playback playback;
  k4n::synchro::Configuration synchro;
  k4n::processing::Image* k4n_image;
  k4n::utils::Configuration* k4n_config;
  k4n::gui::Playback* gui_playback;
};


}
