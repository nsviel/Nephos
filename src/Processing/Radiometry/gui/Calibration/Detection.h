#pragma once

#include <Renderer/gui/Stream.h>

namespace dyn::base{class Sensor;}
namespace rad{class Node;}
namespace rad::calibration{class Structure;}
namespace rad::calibration{class Process;}
namespace rnd::gui{class Stream;}
namespace dat::element{class Image;}


namespace rad::gui::calibration{

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
  void detection_image(dyn::base::Sensor* sensor);
  void parameter_canny();
  void parameter_hough();

private:
  rad::calibration::Structure* rad_struct;
  rad::calibration::Process* rad_process;
  rnd::gui::Stream* stream;
  dat::elm::Image* dat_image;
};

}
