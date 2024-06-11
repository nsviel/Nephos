#pragma once

#include <Radiometry/src/Detection/Sphere/Glyph/Sphere.h>


namespace rad::detection::structure{

struct Ransac{
  //---------------------------

  int nb_iter = 1000;
  int nb_sample = 50;
  float thres_sphere = 0.01;
  float thres_radius = 0.02;
  float search_lambda = 0.7;
  float sphere_diameter = 0.139;
  glm::vec3 current_pose = vec3(0, 0, 0);
  rad::detection::glyph::Sphere* glyph;

  //---------------------------
};

}
