#pragma once

#include <Kinect/src/Structure/Sensor.h>

namespace k4n{class Node;}
namespace k4n::processing::image{class Thread;}
namespace k4n::capture{class Configuration;}
namespace k4n::gui{class Capture;}
namespace dyn::element{class Sensor;}


namespace k4n::capture{

class Sensor : public k4n::structure::Sensor
{
public:
  //Constructor / Destructor
  Sensor(k4n::Node* node_k4n, int index);
  ~Sensor();

public:
  //Main function
  void thread_init();
  void thread_loop();
  void thread_end();

  //Subfunction
  k4a::capture* manage_new_capture();
  void manage_old_capture(k4a::capture* capture);
  void manage_pause();
  void gui_config();

private:
  k4n::processing::image::Thread* k4n_image;
  k4n::capture::Configuration* k4n_config;
  k4n::gui::Capture* gui_capture;
  dyn::element::Sensor* dyn_sensor;
};


}
