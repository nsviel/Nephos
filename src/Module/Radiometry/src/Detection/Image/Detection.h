#pragma once

#include <Utility/Specific/Common.h>

namespace rad{class Node;}
namespace rad{class Structure;}
namespace dat::base{class Sensor;}
namespace utl::thread{class Pool;}
namespace utl::media{class Image;}
namespace rad::detection::image{class Glyph;}
namespace rad::detection::image{class Hough;}
namespace rad::detection::utils{class Image;}


namespace rad::detection::image{

class Detection
{
public:
  //Constructor / Destructor
  Detection(rad::Node* node_radio);
  ~Detection();

public:
  //Main function
  void start_thread(dat::base::Sensor* sensor, utl::media::Image* image);
  void run_thread(dat::base::Sensor* sensor, utl::media::Image* image);
  void wait_thread();

  //Subfunction
  void detect_circle_in_image(dat::base::Sensor* sensor, utl::media::Image* image);
  void draw_detection_image();
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