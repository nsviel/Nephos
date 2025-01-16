#pragma once

#include <glm/glm.hpp>
#include <memory>
#include <vector>

namespace k4n{class Node;}
namespace k4n{class Structure;}
namespace k4n::base{class Sensor;}
namespace utl::base{class Data;}
namespace dat::atr::field{class Manager;}
namespace dat::base{class Sensor;}
namespace dat::atr{class Location;}


namespace k4n::cloud{

class Intensity
{
public:
  //Constructor / Destructor
  Intensity(k4n::Node* node_k4n);
  ~Intensity();

public:
  //Main function
  void extract_data(k4n::base::Sensor& sensor);

  //Subfunction
  void extraction_data(k4n::base::Sensor& sensor);
  void extraction_transfer(k4n::base::Sensor& sensor);

private:
  k4n::Structure* k4n_struct;
  dat::atr::field::Manager* atr_field;
  dat::atr::Location* atr_location;
};

}
