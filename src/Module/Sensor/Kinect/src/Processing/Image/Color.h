#pragma once

#include <k4a/k4a.hpp>
#include <string>

namespace k4n{class Node;}
namespace k4n::structure{class Sensor;}
namespace dat::element{class Image;}


namespace k4n::processing::image{

class Color
{
public:
  //Constructor / Destructor
  Color(k4n::Node* node_k4n);
  ~Color();

public:
  //Main function
  void find_data_color(k4n::structure::Sensor* sensor);

  //Subfunction
  void retrieve_data(k4n::structure::Sensor* sensor);
  void retrieve_image(k4n::structure::Sensor* sensor);
  std::string retrieve_format(k4a_image_format_t color_format);

private:
  dat::element::Image* dat_image;
};

}
