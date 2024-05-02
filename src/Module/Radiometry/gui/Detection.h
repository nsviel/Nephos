#pragma once

#include <Utility/Specific/Common.h>

namespace k4n::dev{class Sensor;}
namespace rad{class Node;}
namespace rad{class Structure;}
namespace rad::detection{class Hough;}
namespace gui::element{class Stream;}
namespace gui_element = gui::element;


namespace rad::gui{

class Detection
{
public:
  //Constructor / Destructor
  Detection(rad::Node* node_radio);
  ~Detection();

public:
  //Main function
  void draw_detection(k4n::dev::Sensor* sensor);

  //Subfunction
  void detection_parameter(k4n::dev::Sensor* sensor);
  void canny_parameter(k4n::dev::Sensor* sensor);
  void hough_parameter(k4n::dev::Sensor* sensor);
  void ransac_parameter(k4n::dev::Sensor* sensor);
  void draw_result(k4n::dev::Sensor* sensor);

private:
  rad::Structure* radio_struct;
  rad::detection::Hough* radio_hough;
  gui_element::Stream* stream;
};

}
