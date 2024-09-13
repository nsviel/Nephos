#pragma once

#include <memory>

namespace dat::base{class Sensor;}
namespace rad{class Node;}
namespace rad::cal{class Structure;}
namespace rad::cal{class Process;}
namespace dat::img::gui{class Stream;}
namespace dat::img{class Image;}


namespace rad::cal::gui{

class Detection
{
public:
  //Constructor / Destructor
  Detection(rad::Node* node_radio);
  ~Detection();

public:
  //Main function
  void draw_tab(dat::base::Sensor& sensor);

  //Subfunction
  void detection_step();
  void detection_parameter();
  void detection_image(dat::base::Sensor& sensor);
  void parameter_canny();
  void parameter_hough();

private:
  rad::cal::Structure* rad_struct;
  rad::cal::Process* rad_process;
  dat::img::gui::Stream* stream;
  dat::img::Image* dat_image;
};

}
