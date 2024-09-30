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

class Depth_to_color
{
public:
  //Constructor / Destructor
  Depth_to_color(k4n::Node* node_k4n);
  ~Depth_to_color();

public:
  //Main function
  void make_transformation(k4n::base::Sensor& sensor);

  //Subfunction
  void find_depth_to_color(k4n::base::Sensor& sensor);
  bool check_data(k4n::base::Sensor& sensor);

private:

};

}
