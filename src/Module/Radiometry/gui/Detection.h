#pragma once

#include <Render/src/Stream.h>
#include <Utility/Specific/Common.h>

namespace dyn{class Structure;}
namespace dyn::base{class Sensor;}
namespace rad{class Node;}
namespace rad::detection{class Structure;}
namespace rad::detection{class Node;}
namespace rad::detection::image{class Circle;}
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
  void detection_stats();
  void detection_image();

  //Parameter function
  void parameter_canny();
  void parameter_hough();
  void parameter_ransac();

  //Subfunction
  void display_state(int step, int data);

private:
  dyn::Structure* dyn_struct;
  rad::detection::Structure* rad_struct;
  rad::detection::Node* node_detection;
  rad::detection::image::Circle* rad_circle;
  rnd::Stream* stream;
};

}
