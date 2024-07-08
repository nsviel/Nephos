#pragma once

#include <image/turbojpeg.h>
#include <k4a/k4a.hpp>
#include <stdint.h>
#include <vector>
#include <string>

namespace k4n{class Node;}
namespace k4n{class Structure;}
namespace k4n::base{class Sensor;}


namespace k4n::processing::image{

class Transformation
{
public:
  //Constructor / Destructor
  Transformation(k4n::Node* node_k4n);
  ~Transformation();

public:
  //Main function
  void make_transformation(k4n::base::Sensor* sensor);

  //Subfunction
  void find_depth_to_color(k4n::base::Sensor* sensor);
  void find_color_to_depth(k4n::base::Sensor* sensor);

private:
  k4n::Structure* k4n_struct;
};

}
