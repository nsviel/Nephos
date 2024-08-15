#pragma once

#include <vector>
#include <glm/glm.hpp>

namespace utl::base{class Data;}
namespace utl::base{class Attribut;}
namespace utl::media{class Image;}


namespace dat::img{

class Converter
{
public:
  //Constructor / Destructor
  Converter();
  ~Converter();

public:
  //Main function
  void convert_normal_to_image(utl::base::Data* data, utl::media::Image* image);
  void convert_intensity_to_image(utl::base::Data* data, utl::media::Image* image);
  void convert_spherical_pc_to_image(utl::base::Data* data, utl::media::Image* image);
  void convert_whole_spherical_pc_to_image(utl::base::Data* data, utl::media::Image* image);
  void convert_color_to_image(utl::base::Data* data, utl::media::Image* image);

private:
  utl::base::Attribut* utl_attribut;
};

}
