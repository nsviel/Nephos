#pragma once

#include <Kinect/src/Structure/Sensor.h>

namespace k4n{class Node;}
namespace k4n::capture{class Capture;}
namespace k4n::processing::cloud{class Data;}
namespace k4n::processing::image{class Data;}
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
  void manage_gui();

private:
  k4n::capture::Capture* k4n_capture;
  k4n::processing::image::Data* k4n_image;
  k4n::processing::cloud::Data* k4n_cloud;
  k4n::gui::Capture* gui_capture;
  dyn::prc::cloud::Operation* dyn_operation;
  dat::sensor::Pool* thr_pool;
};


}
