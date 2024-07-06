#pragma once

#include <k4a/k4a.hpp>

namespace k4n{class Node;}
namespace k4n::structure{class Sensor;}
namespace k4n::processing{class Operation;}
namespace dat::element{class Image;}
namespace dyn{class Structure;}


namespace k4n::processing::image{

class Infrared
{
public:
  //Constructor / Destructor
  Infrared(k4n::Node* node_k4n);
  ~Infrared();

public:
  //Main function
  void extract_data(k4n::structure::Sensor* sensor);

  //Subfunction
  void retrieve_data(k4n::structure::Sensor* sensor);
  void retrieve_image(k4n::structure::Sensor* sensor);
  void convert_image_into_color(k4n::structure::Sensor* sensor);
  std::string retrieve_format(k4a_image_format_t color_format);

private:
  k4n::processing::Operation* k4n_operation;
  dat::element::Image* dat_image;
  dyn::Structure* dyn_struct;
};

}
