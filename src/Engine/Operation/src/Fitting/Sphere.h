#pragma once

#include <Utility/Specific/common.h>


namespace ope::fitting{

class Sphere
{
public:
  Sphere();
  ~Sphere();

public:
  //Sphere fitting
  void find_sphere_in_cloud(vector<vec3>& xyz, vec3& center, float& radius);
  void find_sphere_in_image(utl::media::Image* image);
  void find_sphere_in_image_with_canny(utl::media::Image* image);

private:
};

}
