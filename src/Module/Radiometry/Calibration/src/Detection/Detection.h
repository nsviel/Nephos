#pragma once

namespace rad::cal{class Node;}
namespace rad::cal{class Structure;}
namespace rad::cal{class Image;}
namespace rad::cal{class Rectangle;}
namespace dat::base{class Sensor;}
namespace sys::thread::task{class Pool;}
namespace utl::media{class Image;}
namespace dat::elm{class Image;}


namespace rad::cal{

class Detection
{
public:
  //Constructor / Destructor
  Detection(rad::cal::Node* node_detection);
  ~Detection();

public:
  //Main function
  void start_thread(dat::base::Sensor* sensor);
  void run_thread(dat::base::Sensor* sensor);
  void wait_thread();

  //Subfunction
  void make_shape_detection(dat::base::Sensor* sensor, utl::media::Image* image, utl::media::Image* output);

private:
  sys::thread::task::Pool* thread_pool;
  rad::cal::Structure* rad_struct;
  rad::cal::Image* rad_image;
  rad::cal::Rectangle* rad_rectangle;
  dat::elm::Image* dat_image;

  bool thread_idle = true;
};

}
