#pragma once

#include <Utility/Specific/Common.h>

namespace k4n{class Node;}
namespace k4n::dev{class Sensor;}
namespace k4n::structure{class K4N;}
namespace radio::detection{class Glyph;}
namespace radio::detection{class Hough;}
namespace radio::matching{class Image;}


namespace radio::detection{

class Detector
{
public:
  //Constructor / Destructor
  Detector(k4n::Node* node_k4n);
  ~Detector();

public:
  //Main function
  void make_sphere_detection(k4n::dev::Sensor* sensor);

  //Subfunction
  void detect_circle_in_image(k4n::dev::Sensor* sensor);
  void draw_detection_image(k4n::dev::Sensor* sensor);
  void draw_detection_glyph(k4n::dev::Sensor* sensor);

private:
  k4n::structure::K4N* k4n_struct;
  radio::detection::Glyph* k4n_glyph;
  radio::detection::Hough* k4n_hough;
  radio::matching::Image* k4n_image;
};

}
