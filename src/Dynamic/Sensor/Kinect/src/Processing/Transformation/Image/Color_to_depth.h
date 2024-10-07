#pragma once

#include <image/turbojpeg.h>
#include <k4a/k4a.hpp>
#include <stdint.h>
#include <memory>
#include <vector>
#include <string>

namespace k4n{class Node;}
namespace k4n::base{class Sensor;}


namespace k4n::transformation{

class Color_to_depth
{
public:
  //Constructor / Destructor
  Color_to_depth(k4n::Node* node_k4n);
  ~Color_to_depth();

public:
  //Main function
  void make_transformation(k4n::base::Sensor& sensor);

  //Subfunction
  void k4a_color_to_depth(k4n::base::Sensor& sensor);
  bool check_data(k4n::base::Sensor& sensor);

private:
};

}
