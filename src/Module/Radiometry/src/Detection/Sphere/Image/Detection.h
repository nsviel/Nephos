#pragma once

#include <Utility/Specific/Common.h>

namespace rad::detection{class Node;}
namespace rad::detection{class Structure;}
namespace dyn::base{class Sensor;}
namespace utl::thread{class Pool;}
namespace utl::media{class Image;}
namespace rad::detection::sphere{class Glyph;}
namespace rad::detection::image{class Hough;}
namespace rad::detection::image{class Image;}
namespace dat{class Image;}


namespace rad::detection::image{

class Detection
{
public:
  //Constructor / Destructor
  Detection(rad::detection::Node* node_detection);
  ~Detection();

public:
  //Main function
  void start_thread(dyn::base::Sensor* sensor);
  void run_thread(dyn::base::Sensor* sensor);
  void wait_thread();

  //Subfunction
  void make_shape_detection(dyn::base::Sensor* sensor, utl::media::Image* image);

private:
  utl::thread::Pool* thread_pool;
  rad::detection::Structure* rad_struct;
  rad::detection::sphere::Glyph* rad_glyph;
  rad::detection::image::Hough* rad_hough;
  rad::detection::image::Image* rad_image;
  dat::Image* dat_image;

  std::thread thread;
  bool thread_idle = true;
};

}
