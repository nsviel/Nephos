#pragma once

#include <Renderer/gui/Stream.h>

namespace dyn::prc::base{class Sensor;}
namespace rad{class Node;}
namespace rad::cal{class Structure;}
namespace rad::cal{class Process;}
namespace rnd::gui{class Stream;}
namespace dat::elm{class Image;}


namespace rad::cal::gui{

class Detection
{
public:
  //Constructor / Destructor
  Detection(rad::Node* node_radio);
  ~Detection();

public:
  //Main function
  void draw_tab(dyn::prc::base::Sensor* sensor);

  //Subfunction
  void detection_step();
  void detection_parameter();
  void detection_image(dyn::prc::base::Sensor* sensor);
  void parameter_canny();
  void parameter_hough();

private:
  rad::cal::Structure* rad_struct;
  rad::cal::Process* rad_process;
  rnd::gui::Stream* stream;
  dat::elm::Image* dat_image;
};

}
