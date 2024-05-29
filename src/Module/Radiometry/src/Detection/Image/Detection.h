#pragma once

#include <Utility/Specific/Common.h>

namespace rad{class Node;}
namespace rad{class Structure;}
namespace dat::base{class Sensor;}
namespace utl::thread{class Pool;}
namespace utl::media{class Image;}
namespace rad::detection::image{class Glyph;}
namespace rad::detection::image{class Circle;}
namespace rad::detection::image{class Image;}
namespace rad::detection::image{class Rectangle;}


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
  void detect_circle_in_image(utl::media::Image* image);
  void detect_rectangle_in_image(utl::media::Image* image);

private:
  utl::thread::Pool* thread_pool;
  rad::Structure* rad_struct;
  rad::detection::image::Glyph* rad_glyph;
  rad::detection::image::Circle* rad_circle;
  rad::detection::image::Image* rad_image;
  rad::detection::image::Rectangle* rad_rectangle;

  bool thread_idle = true;
};

}
