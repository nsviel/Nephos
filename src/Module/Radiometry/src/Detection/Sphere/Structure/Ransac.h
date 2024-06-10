#pragma once

#include <Radiometry/src/Detection/Sphere/Glyph/Sphere.h>


namespace rad::detection::structure{

struct Ransac{
  //---------------------------

  int nb_iter = 1000;
  float thres_sphere = 0.005;
  float thres_pose = 0.1;
  float thres_radius = 0.02;

  float search_lambda = 2;
  float search_radius = 0.5;

  float sphere_diameter = 0.139;
  glm::vec3 current_pose = vec3(0, 0, 0);
  rad::detection::glyph::Sphere* glyph;

  //---------------------------
};

}
