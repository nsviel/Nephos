#pragma once

#include <Renderer/gui/Stream.h>

namespace dyn::base{class Sensor;}
namespace rad{class Node;}
namespace rad::correction{class Structure;}
namespace rad::correction{class Process;}
namespace rad::correction::image{class Hough;}
namespace itf::gui{class Stream;}
namespace dat::element{class Image;}


namespace rad::gui::correction{

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

private:
  rad::correction::Structure* rad_struct;
  rad::correction::Process* rad_process;
  rad::correction::image::Hough* rad_hough;
  itf::gui::Stream* stream;
  dat::element::Image* dat_image;
};

}
