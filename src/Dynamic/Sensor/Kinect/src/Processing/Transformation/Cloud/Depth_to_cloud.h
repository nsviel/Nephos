#pragma once

#include <glm/glm.hpp>
#include <memory>
#include <vector>

namespace k4n{class Node;}
namespace k4n{class Structure;}
namespace k4n::base{class Sensor;}
namespace k4n::cloud{class Color;}
namespace k4n::cloud{class Intensity;}
namespace k4n::cloud{class Location;}
namespace utl::base{class Data;}
namespace dat::atr{class Field;}
namespace dat::base{class Sensor;}
namespace dat::atr{class Location;}


namespace k4n::data{

class Depth_to_cloud
{
public:
  //Constructor / Destructor
  Depth_to_cloud(k4n::Node* node_k4n);
  ~Depth_to_cloud();

public:
  //Main function
  void make_transformation(k4n::base::Sensor& sensor);

  //Subfunction
  bool check_condition(k4n::base::Sensor& sensor);
  void extraction_init(k4n::base::Sensor& sensor);

private:
  k4n::Structure* k4n_struct;
  k4n::cloud::Color* k4n_color;
  k4n::cloud::Intensity* k4n_intensity;
  k4n::cloud::Location* k4n_location;
  dat::atr::Field* atr_field;
  dat::atr::Location* atr_location;
};

}
