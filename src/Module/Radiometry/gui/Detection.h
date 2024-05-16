#pragma once

#include <Render/src/Stream.h>
#include <Utility/Specific/Common.h>

namespace dat::base{class Sensor;}
namespace rad{class Node;}
namespace rad{class Structure;}
namespace rad{class Detection;}
namespace rad::detection{class Hough;}
namespace rnd{class Stream;}


namespace rad::gui{

class Detection
{
public:
  //Constructor / Destructor
  Detection(rad::Node* node_radio);
  ~Detection();

public:
  //Main function
  void draw_detection_tab();

  //Subfunction
  void detection_step();
  void detection_parameter();
  void parameter_canny();
  void parameter_hough();
  void parameter_ransac();
  void display_image();

private:
  rad::Detection* rad_detection;
  rad::Structure* rad_struct;
  rad::detection::Hough* rad_hough;
  rnd::Stream* stream;
};

}
