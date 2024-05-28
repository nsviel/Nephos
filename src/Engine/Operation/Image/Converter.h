#pragma once

#include <glm/glm.hpp>

namespace dat::base{class Entity;}
namespace ope::image{class Manager;}


namespace ope::image{

class Converter
{
public:
  //Constructor / Destructor
  Converter();
  ~Converter();

public:
  //Main function
  void convert_normal_to_image(dat::base::Entity* entity);

private:
  ope::image::Manager* ope_image;
};

}
