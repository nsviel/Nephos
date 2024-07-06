#pragma once

#include <k4a/k4a.hpp>

namespace k4n{class Node;}
namespace k4n::structure{class Sensor;}
namespace dat::element{class Image;}


namespace k4n::processing::image{

class Depth
{
public:
  //Constructor / Destructor
  Depth(k4n::Node* node_k4n);
  ~Depth();

public:
  //Main function
  void extract_data(k4n::structure::Sensor* sensor);

  //Subfunction
  void retrieve_data(k4n::structure::Sensor* sensor);
  void retrieve_image(k4n::structure::Sensor* sensor);
  void convert_image_into_color(k4n::structure::Sensor* sensor);
  std::string retrieve_format(k4a_image_format_t color_format);
  void find_depth_mode_range(k4n::structure::Sensor* sensor);

private:
  dat::element::Image* dat_image;
};

}
