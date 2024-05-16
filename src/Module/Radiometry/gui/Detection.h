#pragma once

#include <GUI/Media/Stream.h>
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
  void draw_detection();

  //Subfunction
  void detection_parameter();
  void canny_parameter();
  void hough_parameter();
  void ransac_parameter();
  void draw_result();

private:
  rad::Structure* radio_struct;
  rad::detection::Hough* radio_hough;
  gui_media::Stream* stream;
};

}
