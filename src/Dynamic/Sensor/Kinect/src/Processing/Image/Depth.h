#pragma once

#include <k4a/k4a.hpp>
#include <memory>

namespace k4n{class Node;}
namespace k4n::base{class Sensor;}
namespace dat::img{class Image;}
namespace dat::img{class Depth;}


namespace k4n::image{

class Depth
{
public:
  //Constructor / Destructor
  Depth(k4n::Node* node_k4n);
  ~Depth();

public:
  //Main function
  void extract_data(k4n::base::Sensor& sensor);

  //Data function
  void retrieve_data(k4n::base::Sensor& sensor);
  void retrieve_raw_image(k4n::base::Sensor& sensor);
  void retrieve_colored_image(k4n::base::Sensor& sensor);

  //Subfunction
  std::string retrieve_format(k4a_image_format_t color_format);
  void convert_buffer_into_color(k4n::base::Sensor& sensor);
  void convert_buffer_into_uint16(k4n::base::Sensor& sensor);
  void find_depth_mode_range(k4n::base::Sensor& sensor);

private:
  dat::img::Image* dat_image;
  dat::img::Depth* dat_depth;
};

}
