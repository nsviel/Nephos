#pragma once

#include <k4a/k4a.hpp>
#include <memory>

namespace k4n{class Node;}
namespace k4n::base{class Sensor;}
namespace k4n::depth{class Format;}
namespace dat::img{class Image;}
namespace dat::img{class Depth;}


namespace k4n::depth{

class Data
{
public:
  //Constructor / Destructor
  Data(k4n::Node* node_k4n);
  ~Data();

public:
  //Main function
  void extract_data(k4n::base::Sensor& sensor);

  //Subfunction
  void retrieve_data(k4n::base::Sensor& sensor);
  void retrieve_raw_image(k4n::base::Sensor& sensor);
  void retrieve_colored_image(k4n::base::Sensor& sensor);

private:
  dat::img::Image* dat_image;
  dat::img::Depth* dat_depth;
  k4n::depth::Format* k4n_format;
};

}
