#pragma once

#include <thread>

namespace rad::correction{class Node;}
namespace rad::correction{class Structure;}
namespace dyn::prc::base{class Sensor;}
namespace sys::thread::task{class Pool;}
namespace utl::media{class Image;}
namespace rad::correction{class Glyph;}
namespace rad::correction::image{class Hough;}
namespace rad::correction::image{class Image;}
namespace dat::elm{class Image;}


namespace rad::correction::image{

class Detection
{
public:
  //Constructor / Destructor
  Detection(rad::correction::Node* node_correction);
  ~Detection();

public:
  //Main function
  void start_thread(dyn::base::Sensor* sensor);
  void run_thread(dyn::base::Sensor* sensor);
  void wait_thread();

  //Subfunction
  void make_shape_detection(dyn::base::Sensor* sensor, utl::media::Image* image, utl::media::Image* output);

private:
  sys::thread::task::Pool* thread_pool;
  rad::correction::Structure* rad_struct;
  rad::correction::Glyph* rad_glyph;
  rad::correction::image::Hough* rad_hough;
  rad::correction::image::Image* rad_image;
  dat::elm::Image* dat_image;

  std::thread thread;
  bool thread_idle = true;
};

}
