#pragma once

#include <Utility/Specific/Common.h>

namespace radio{class Structure;}
namespace k4n::dev{class Sensor;}
namespace k4n::thread{class Pool;}
namespace radio::detection{class Glyph;}
namespace radio::detection{class Hough;}
namespace radio::matching{class Image;}


namespace radio::detection{

class Identification
{
public:
  //Constructor / Destructor
  Identification(radio::Structure* radio_struct);
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
  radio::Structure* radio_struct;
  radio::detection::Glyph* radio_glyph;
  radio::detection::Hough* radio_hough;
  radio::matching::Image* radio_image;

  bool idle = true;
};

}
