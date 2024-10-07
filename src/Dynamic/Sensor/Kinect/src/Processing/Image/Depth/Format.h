#pragma once

#include <k4a/k4a.hpp>
#include <memory>

namespace k4n{class Node;}
namespace k4n::base{class Sensor;}
namespace dat::img{class Image;}
namespace dat::img{class Depth;}


namespace k4n::depth{

class Format
{
public:
  //Constructor / Destructor
  Format(k4n::Node* node_k4n);
  ~Format();

public:
  //Main function
  std::string retrieve_format(k4a_image_format_t color_format);

  //Subfunction
  void convert_buffer_into_color(k4n::base::Sensor& sensor);
  void convert_buffer_into_uint16(k4n::base::Sensor& sensor);

private:
  dat::img::Image* dat_image;
  dat::img::Depth* dat_depth;
};

}
