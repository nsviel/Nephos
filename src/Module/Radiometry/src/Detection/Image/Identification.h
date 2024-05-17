#pragma once

#include <Utility/Specific/Common.h>

namespace rad{class Node;}
namespace rad{class Structure;}
namespace dat::base{class Sensor;}
namespace utl::thread{class Pool;}
namespace rad::detection::image{class Glyph;}
namespace rad::detection::image{class Hough;}
namespace rad::detection::utils{class Image;}


namespace rad::detection{

class Identification
{
public:
  //Constructor / Destructor
  Identification(rad::Node* node_radio);
  ~Identification();

public:
  //Main function
  void start_thread(dat::base::Sensor* sensor);
  void run_thread(dat::base::Sensor* sensor);
  void wait_thread();

  //Subfunction
  void make_sphere_detection(dat::base::Sensor* sensor);
  void detect_circle_in_image(dat::base::Sensor* sensor);
  void draw_detection_image(dat::base::Sensor* sensor);
  void draw_detection_glyph(dat::base::Sensor* sensor);

private:
  utl::thread::Pool* thread_pool;
  rad::Structure* rad_struct;
  rad::detection::image::Glyph* rad_glyph;
  rad::detection::image::Hough* rad_hough;
  rad::detection::utils::Image* rad_image;

  bool idle = true;
};

}
