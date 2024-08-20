#pragma once

#include <Radiometry/Correction/src/Detection/Glyph/Sphere.h>
#include <glm/glm.hpp>
#include <vector>


namespace rad::cor::structure{

struct Ransac{
  //---------------------------

  int nb_iter = 100;
  int nb_sample = 50;
  int idx_nearest = -1;
  float thres_sphere = 0.02;
  float thres_radius = 0.02;
  float search_radius = 0.15;
  float sphere_diameter = 0.139;
  glm::vec3 current_pose = glm::vec3(0, 0, 0);
  rad::cor::glyph::Sphere* glyph;

  std::vector<glm::vec3> search_xyz;
  std::vector<glm::vec3> search_Nxyz;
  std::vector<float> search_Is;

  //---------------------------
};

}
