#pragma once

#include <Utility/Specific/common.h>


namespace ope::attribut{

class Fitting
{
public:
  Fitting();
  ~Fitting();

public:
  //Sphere fitting
  void find_sphere(utl::type::Entity* entity, vec3& center, float& radius);

private:
};

}
