#pragma once

#include <k4a/k4a.hpp>
#include <memory>

namespace k4n{class Node;}
namespace k4n::base{class Sensor;}
namespace dat::img{class Image;}
namespace dat::img{class Depth;}


namespace k4n::depth{

class Texture
{
public:
  //Constructor / Destructor
  Texture(k4n::Node* node_k4n);
  ~Texture();

public:
  //Main function
  void retrieve_raw_image(k4n::base::Sensor& sensor);
  void retrieve_colored_image(k4n::base::Sensor& sensor);

private:
  dat::img::Image* dat_image;
  dat::img::Depth* dat_depth;
};

}
