#pragma once

#include <Radiometry/src/Correction/Detection/Glyph/Sphere.h>


namespace rad::correction::structure{

struct Ransac{
  //---------------------------

  int nb_iter = 100;
  int nb_sample = 50;
  int idx_nearest = -1;
  float thres_sphere = 0.02;
  float thres_radius = 0.02;
  float search_radius = 0.15;
  float sphere_diameter = 0.139;
  glm::vec3 current_pose = vec3(0, 0, 0);
  rad::correction::glyph::Sphere* glyph;

  vector<vec3> search_xyz;
  vector<vec3> search_Nxyz;
  vector<float> search_Is;

  //---------------------------
};

}
