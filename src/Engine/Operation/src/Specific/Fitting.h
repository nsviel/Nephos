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
  void find_sphere_in_cloud(utl::type::Entity* entity, vec3& center, float& radius);
  void find_sphere_in_image(utl::media::Image* image);
  void find_sphere_in_image_with_canny(utl::media::Image* image);

private:
};

}
