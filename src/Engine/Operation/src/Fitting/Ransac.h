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
  void ransac_sphere_in_cloud(std::vector<vec3>& xyz, vec3& best_center, float& best_radius, float radius_to_find);

  inline int* get_num_iteration(){return num_iter;}
  inline float* get_threshold_sphere(){return threshold_sphere;}
  inline float* get_threshold_pose(){return threshold_pose;}
  inline float* get_threshold_radius(){return threshold_radius;}

private:
  ope::fitting::Sphere* ope_sphere;

  int num_iter = 100;
  float threshold_sphere = 0.005;
  float threshold_pose = 0.1;
  float threshold_radius = 0.02;
};

}
