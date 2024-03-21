#pragma once

#include <Utility/Specific/common.h>

namespace k4n{class Node;}
namespace k4n::dev{class Sensor;}
namespace k4n::detection{class Glyph;}
namespace k4n::detection{class Hough;}
namespace k4n::matching{class Image;}


namespace k4n::detection{

class Detection
{
public:
  //Constructor / Destructor
  Detection(k4n::Node* node_k4n);
  ~Detection();

public:
  //Main function
  void make_sphere_detection(k4n::dev::Sensor* sensor);

  //Subfunction
  void detect_circle_in_image(k4n::dev::Sensor* sensor);

private:
  k4n::detection::Glyph* k4n_glyph;
  k4n::detection::Hough* k4n_hough;
  k4n::matching::Image* k4n_image;
};

}
