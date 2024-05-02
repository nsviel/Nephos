#pragma once

#include <Utility/Specific/Common.h>

namespace rad{class Node;}
namespace rad{class Structure;}
namespace dat::base{class Sensor;}
namespace utl::thread{class Pool;}
namespace rad::detection{class Glyph;}
namespace rad::detection{class Hough;}
namespace rad::matching{class Image;}


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
  rad::Structure* radio_struct;
  rad::detection::Glyph* radio_glyph;
  rad::detection::Hough* radio_hough;
  rad::matching::Image* radio_image;

  bool idle = true;
};

}
