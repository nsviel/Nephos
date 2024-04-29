#pragma once

#include <Utility/Specific/Common.h>

namespace rad{class Structure;}
namespace k4n::dev{class Sensor;}
namespace k4n::thread{class Pool;}
namespace rad::detection{class Glyph;}
namespace rad::detection{class Hough;}
namespace rad::matching{class Image;}


namespace rad::detection{

class Identification
{
public:
  //Constructor / Destructor
  Identification(rad::Structure* radio_struct);
  ~Identification();

public:
  //Main function
  void start_thread(k4n::dev::Sensor* sensor);
  void run_thread(k4n::dev::Sensor* sensor);
  void wait_thread();

  //Subfunction
  void make_sphere_detection(k4n::dev::Sensor* sensor);
  void detect_circle_in_image(k4n::dev::Sensor* sensor);
  void draw_detection_image(k4n::dev::Sensor* sensor);
  void draw_detection_glyph(k4n::dev::Sensor* sensor);

private:
  k4n::thread::Pool* k4n_pool;
  rad::Structure* radio_struct;
  rad::detection::Glyph* radio_glyph;
  rad::detection::Hough* radio_hough;
  rad::matching::Image* radio_image;

  bool idle = true;
};

}