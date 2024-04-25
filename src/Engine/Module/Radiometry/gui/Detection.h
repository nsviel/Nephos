#pragma once

#include <Utility/Specific/Common.h>

namespace k4n::dev{class Sensor;}
namespace radio{class Structure;}
namespace radio::detection{class Hough;}
namespace eng::gui{class Stream;}


namespace radio::gui{

class Detection
{
public:
  //Constructor / Destructor
  Detection(radio::Structure* radio_struct);
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
  radio::Structure* radio_struct;
  radio::detection::Hough* radio_hough;
  eng::gui::Stream* stream;
};

}
