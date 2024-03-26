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
  void ransac_find_sphere_in_cloud(std::vector<vec3>& xyz, vec3& best_center, float& best_radius, int num_iter, float inlier_threshold);
  void find_sphere_in_cloud(vector<vec3>& xyz, vec3& center, float& radius);
  void find_sphere_in_image(utl::media::Image* image);
  void find_sphere_in_image_with_canny(utl::media::Image* image);

private:
};

}
