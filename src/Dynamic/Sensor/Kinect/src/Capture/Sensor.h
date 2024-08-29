#pragma once

#include <Kinect/src/Structure/Sensor.h>

namespace k4n{class Node;}
namespace k4n{class Processing;}
namespace k4n::capture{class Configuration;}
namespace k4n::capture{class Capture;}
namespace k4n::gui{class Capture;}
namespace dat::elm{class Sensor;}


namespace k4n::capture{

class Sensor : public k4n::base::Sensor
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
  void manage_capture();
  void manage_gui();

private:
  k4n::Processing* k4n_processing;
  k4n::capture::Configuration* k4n_config;
  k4n::capture::Capture* k4n_capture;
  k4n::gui::Capture* gui_capture;
  dat::elm::Sensor* dat_sensor;
};


}
