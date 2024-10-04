#pragma once

#include <k4a/k4a.hpp>
#include <memory>
#include <string>

namespace k4n{class Node;}
namespace k4n::base{class Sensor;}
namespace dat::img{class Image;}


namespace k4n::color{

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
  uint8_t* retrieve_bgra_from_yuy2(const uint8_t* yuy2Image, int width, int height);
  void retrieve_data_from_capture(k4a::image& image, std::vector<uint8_t>& data, std::string& format);
  void retrieve_bgra_from_mjpeg(k4a::image& image, std::vector<uint8_t>& data);
  void convert_bgra_to_rgba(k4n::base::Sensor& sensor);

private:
  dat::img::Image* dat_image;
};

}
