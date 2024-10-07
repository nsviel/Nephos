#pragma once

#include <glm/glm.hpp>
#include <memory>
#include <vector>

namespace k4n{class Node;}
namespace k4n{class Structure;}
namespace k4n::base{class Sensor;}
namespace utl::base{class Data;}
namespace dat::atr{class Field;}
namespace dat::base{class Sensor;}
namespace dat::atr{class Location;}


namespace k4n::cloud{

class Color
{
public:
  //Constructor / Destructor
  Color(k4n::Node* node_k4n);
  ~Color();

public:
  //Main function
  void extract_data(k4n::base::Sensor& sensor);

  //Subfunction
  void extraction_data(k4n::base::Sensor& sensor);
  void extraction_transfer(k4n::base::Sensor& sensor);

private:
  k4n::Structure* k4n_struct;
  dat::atr::Field* atr_field;
  dat::atr::Location* atr_location;
};

}
