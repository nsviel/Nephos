#pragma once

#include <image/turbojpeg.h>
#include <k4a/k4a.hpp>
#include <stdint.h>
#include <vector>
#include <string>

namespace k4n::base{class Sensor;}


namespace k4n::processing::image{

class Color_to_depth
{
public:
  //Constructor / Destructor
  Color_to_depth();
  ~Color_to_depth();

public:
  //Main function
  void make_transformation(k4n::base::Sensor* sensor);

  //Subfunction
  void find_color_to_depth(k4n::base::Sensor* sensor);

private:
};

}
