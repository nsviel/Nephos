#pragma once

#include <glm/glm.hpp>


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

};

}
