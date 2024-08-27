#pragma once

#include <k4a/k4a.hpp>
#include <memory>

namespace k4n{class Node;}
namespace k4n::base{class Sensor;}
namespace dat::elm{class Image;}


namespace k4n::processing::image{

class Depth
{
public:
  //Constructor / Destructor
  Depth(k4n::Node* node_k4n);
  ~Depth();

public:
  //Main function
  void extract_data(std::shared_ptr<k4n::base::Sensor> sensor);

  //Data function
  void retrieve_data(std::shared_ptr<k4n::base::Sensor> sensor);
  void retrieve_image(std::shared_ptr<k4n::base::Sensor> sensor);

  //Subfunction
  std::string retrieve_format(k4a_image_format_t color_format);
  void convert_image_into_color(std::shared_ptr<k4n::base::Sensor> sensor, std::vector<uint8_t>& buffer);
  void find_depth_mode_range(std::shared_ptr<k4n::base::Sensor> sensor);

private:
  dat::elm::Image* dat_image;
};

}
