#pragma once

#include <Utility/Specific/Common.h>

namespace dat::base{class Sensor;}
namespace rad{class Node;}
namespace rad{class Structure;}
namespace rad::detection{class Hough;}
namespace gui::media{class Stream;}
namespace gui_media = gui::media;


namespace rad::gui{

class Detection
{
public:
  //Constructor / Destructor
  Detection(rad::Node* node_radio);
  ~Detection();

public:
  //Main function
  void draw_detection(dat::base::Sensor* sensor);

  //Subfunction
  void detection_parameter(dat::base::Sensor* sensor);
  void canny_parameter(dat::base::Sensor* sensor);
  void hough_parameter(dat::base::Sensor* sensor);
  void ransac_parameter(dat::base::Sensor* sensor);
  void draw_result(dat::base::Sensor* sensor);

private:
  rad::Structure* radio_struct;
  rad::detection::Hough* radio_hough;
  gui_media::Stream* stream;
};

}
