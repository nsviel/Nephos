#pragma once

#include <k4a/k4a.hpp>
#include <memory>
#include <string>

namespace k4n{class Node;}
namespace k4n::color{class Format;}
namespace k4n::colornew{class Structure;}
namespace k4n::base{class Sensor;}
namespace dat::img{class Image;}
namespace dat::base{class Sensor;}


namespace k4n::color{

class Data
{
public:
  //Constructor / Destructor
  Data(k4n::Node* node_k4n);
  ~Data();

public:
  //Main function
  void extract_data(dat::base::Sensor& dat_sensor);

  //Subfunction
  void retrieve_data(k4n::colornew::Structure& color);
  void retrieve_image(k4n::colornew::Structure& color);
  void retrieve_color(k4n::colornew::Structure& color);
  void retrieve_timestamp(k4n::colornew::Structure& color);

private:
  dat::img::Image* dat_image;
  k4n::color::Format* k4a_format;
};

}
