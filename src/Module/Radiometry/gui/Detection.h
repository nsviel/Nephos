#pragma once

#include <Render/src/Stream.h>
#include <Utility/Specific/Common.h>

namespace dyn{class Structure;}
namespace dyn::base{class Sensor;}
namespace rad{class Node;}
namespace rad::detection{class Structure;}
namespace rad::detection::sphere{class Process;}
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
  rad::detection::sphere::Process* sphere_process;
  rad::detection::image::Hough* rad_hough;
  rnd::Stream* stream;
};

}
