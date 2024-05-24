#pragma once

#include <Render/src/Stream.h>
#include <Utility/Specific/Common.h>

namespace dat::base{class Sensor;}
namespace rad{class Node;}
namespace rad{class Structure;}
namespace rad::detection{class Manager;}
namespace rad::detection::image{class Hough;}
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
  void draw_tab();

  //Subfunction
  void detection_step();
  void detection_parameter();
  void parameter_canny();
  void parameter_hough();
  void parameter_ransac();
  void display_image();

private:
  rad::Structure* rad_struct;
  rad::detection::Manager* rad_detection;
  rad::detection::image::Hough* rad_hough;
  rnd::Stream* stream;
};

}
