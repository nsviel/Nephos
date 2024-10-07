#pragma once

#include <k4a/k4a.hpp>
#include <memory>
#include <string>

namespace k4n{class Node;}
namespace k4n::base{class Sensor;}
namespace k4n::color{class Format;}
namespace dat::img{class Image;}


namespace k4n::color{

class Texture
{
public:
  //Constructor / Destructor
  Texture(k4n::Node* node_k4n);
  ~Texture();

public:
  //Main function
  void retrieve_image(k4n::base::Sensor& sensor);

private:
  dat::img::Image* dat_image;
  k4n::color::Format* k4n_format;
};

}
