#pragma once

#include <Utility/Specific/Common.h>

namespace k4n{class Node;}
namespace k4n::dev{class Sensor;}
namespace k4n::structure{class K4N;}
namespace k4n::detection{class Hough;}
namespace eng::gui{class Stream;}


namespace k4n::gui{

class Detection
{
public:
  //Constructor / Destructor
  Detection(k4n::Node* node_k4n);
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
  k4n::structure::K4N* k4n_struct;
  k4n::detection::Hough* k4n_hough;
  eng::gui::Stream* stream;
};

}
