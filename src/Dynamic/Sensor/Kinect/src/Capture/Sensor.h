#pragma once

#include <Kinect/src/Structure/Sensor.h>

namespace k4n{class Node;}
namespace k4n::capture{class Capture;}
namespace k4n::data{class Cloud;}
namespace k4n::data{class Image;}
namespace k4n::gui{class Capture;}
namespace dyn::prc::cloud{class Operation;}
namespace dat::sensor{class Pool;}


namespace k4n::capture{

class Sensor : public k4n::base::Sensor
{
public:
  //Constructor / Destructor
  Sensor(k4n::Node* node_k4n);
  ~Sensor();

public:
  //Main function
  void thread_init();
  void thread_loop();
  void thread_end();

  //Subfunction
  void gui_config();
  void gui_info();
  
private:
  k4n::capture::Capture* k4n_capture;
  k4n::data::Image* k4n_image;
  k4n::data::Cloud* k4n_cloud;
  k4n::gui::Capture* gui_capture;
  dyn::prc::cloud::Operation* dyn_operation;
  dat::sensor::Pool* thr_pool;
};


}
