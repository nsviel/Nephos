#pragma once

#include <Utility/Specific/Common.h>

namespace rad::correction{class Node;}
namespace rad::correction{class Structure;}
namespace dyn::base{class Sensor;}
namespace utl::thread{class Pool;}
namespace utl::media{class Image;}
namespace rad::correction{class Glyph;}
namespace rad::correction::image{class Hough;}
namespace rad::correction::image{class Image;}
namespace dat{class Image;}


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
  void make_shape_detection(dyn::base::Sensor* sensor, utl::media::Image* image);

private:
  utl::thread::Pool* thread_pool;
  rad::correction::Structure* rad_struct;
  rad::correction::Glyph* rad_glyph;
  rad::correction::image::Hough* rad_hough;
  rad::correction::image::Image* rad_image;
  dat::Image* dat_image;

  std::thread thread;
  bool thread_idle = true;
};

}
