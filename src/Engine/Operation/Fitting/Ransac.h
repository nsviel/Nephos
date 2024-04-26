#pragma once

#include <Utility/Specific/Common.h>

namespace ope::fitting{class Sphere;}


namespace ope::fitting{

class Ransac
{
public:
  Ransac();
  ~Ransac();

public:
  //Ransac fitting
  void ransac_sphere_in_cloud(std::vector<vec3>& xyz, vec3& center, float& radius, float radius_to_find);

  inline void set_num_iteration(int value){this->num_iter = value;}
  inline void set_threshold_sphere(float value){this->threshold_sphere = value;}
  inline void set_threshold_pose(float value){this->threshold_pose = value;}
  inline void set_threshold_radius(float value){this->threshold_radius = value;}

private:
  ope::fitting::Sphere* ope_sphere;

  int num_iter = 100;
  float threshold_sphere = 0.005;
  float threshold_pose = 0.1;
  float threshold_radius = 0.02;
};

}
