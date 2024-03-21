#pragma once

#include <Utility/Specific/common.h>

namespace k4n{class Node;}
namespace k4n::dev{class Sensor;}
namespace k4n::calibration{class Glyph;}
namespace k4n::calibration{class Hough;}
namespace k4n::calibration{class Image;}


namespace k4n::registration{

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
  k4n::calibration::Glyph* k4n_glyph;
  k4n::calibration::Hough* k4n_hough;
  k4n::calibration::Image* k4n_image;
};

}
