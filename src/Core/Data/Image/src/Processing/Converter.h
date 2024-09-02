#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <memory>

namespace utl::base{class Data;}
namespace dat::atr{class Field;}
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
  void convert_normal_to_image(utl::base::Data& data, std::shared_ptr<utl::media::Image> image);
  void convert_intensity_to_image(utl::base::Data& data, std::shared_ptr<utl::media::Image> image);
  void convert_spherical_pc_to_image(utl::base::Data& data, std::shared_ptr<utl::media::Image> image);
  void convert_whole_spherical_pc_to_image(utl::base::Data& data, std::shared_ptr<utl::media::Image> image);
  void convert_color_to_image(utl::base::Data& data, std::shared_ptr<utl::media::Image> image);

private:
  dat::atr::Field* atr_field;
};

}