#pragma once

#include <vector>
#include <glm/glm.hpp>

namespace utl::base{class Data;}
namespace utl::media{class Image;}


namespace ope::image{

class Converter
{
public:
  //Constructor / Destructor
  Converter();
  ~Converter();

public:
  //Main function
  void convert_normal_to_image(utl::base::Data* data, utl::media::Image* image);
  void convert_infrared_to_image(utl::base::Data* data, utl::media::Image* image);

private:
};

}
