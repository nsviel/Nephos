#pragma once

#include <Utility/Specific/common.h>

namespace ope::fitting{class Sphere;}


namespace ope::fitting{

class Ransac
{
public:
  Ransac();
  ~Ransac();

public:
  //Ransac fitting
  void ransac_sphere_in_cloud(std::vector<vec3>& xyz, vec3& best_center, float& best_radius, int num_iter, float inlier_threshold);

private:
  ope::fitting::Sphere* ope_sphere;
};

}
