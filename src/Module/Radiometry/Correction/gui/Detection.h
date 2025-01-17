#pragma once

#include <memory>

namespace dat::base{class Sensor;}
namespace rad{class Node;}
namespace rad::cor{class Structure;}
namespace rad::cor{class Process;}
namespace rad::cor::image{class Hough;}
namespace dat::img::gui{class Stream;}
namespace dat::img{class Image;}


namespace rad::cor::gui{

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
  void detection_stats();
  void detection_image(dat::base::Sensor& sensor);

  //Parameter function
  void parameter_canny();
  void parameter_hough();
  void parameter_ransac();

private:
  rad::cor::Structure* rad_struct;
  rad::cor::Process* rad_process;
  rad::cor::image::Hough* rad_hough;
  dat::img::gui::Stream* stream;
  dat::img::Image* dat_image;
};

}
