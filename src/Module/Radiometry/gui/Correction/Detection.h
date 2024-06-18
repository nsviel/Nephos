#pragma once

#include <Render/src/Stream.h>
#include <Utility/Specific/Common.h>

namespace dyn::base{class Sensor;}
namespace rad{class Node;}
namespace rad::correction{class Structure;}
namespace rad::correction{class Process;}
namespace rad::correction::image{class Hough;}
namespace rnd{class Stream;}
namespace dat{class Image;}


namespace rad::gui{

class Detection
{
public:
  //Constructor / Destructor
  Detection(rad::Node* node_radio);
  ~Detection();

public:
  //Main function
  void draw_tab(dyn::base::Sensor* sensor);

  //Subfunction
  void detection_step();
  void detection_parameter();
  void detection_stats();
  void detection_image(dyn::base::Sensor* sensor);

  //Parameter function
  void parameter_canny();
  void parameter_hough();
  void parameter_ransac();

  //Subfunction
  void display_state(int step, int data);

private:
  rad::correction::Structure* rad_struct;
  rad::correction::Process* sphere_process;
  rad::correction::Process* chart_process;
  rad::correction::image::Hough* rad_hough;
  rnd::Stream* stream;
  dat::Image* dat_image;
};

}
