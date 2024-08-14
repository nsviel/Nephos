#pragma once

namespace rad::calibration{class Node;}
namespace rad::calibration{class Structure;}
namespace rad::calibration{class Image;}
namespace rad::calibration{class Rectangle;}
namespace dyn::base{class Sensor;}
namespace utl::thread::task{class Pool;}
namespace utl::media{class Image;}
namespace dat::element{class Image;}


namespace rad::calibration{

class Detection
{
public:
  //Constructor / Destructor
  Detection(rad::calibration::Node* node_detection);
  ~Detection();

public:
  //Main function
  void start_thread(dyn::base::Sensor* sensor);
  void run_thread(dyn::base::Sensor* sensor);
  void wait_thread();

  //Subfunction
  void make_shape_detection(dyn::base::Sensor* sensor, utl::media::Image* image, utl::media::Image* output);

private:
  utl::thread::task::Pool* thread_pool;
  rad::calibration::Structure* rad_struct;
  rad::calibration::Image* rad_image;
  rad::calibration::Rectangle* rad_rectangle;
  dat::element::Image* dat_image;

  bool thread_idle = true;
};

}
