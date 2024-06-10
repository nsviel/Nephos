#pragma once


namespace rad::detection::structure{

struct Ransac{
  //---------------------------

  //Parameter
  int nb_iter = 1000;
  float thres_sphere = 0.005;
  float thres_pose = 0.1;
  float thres_radius = 0.02;
  float search_lambda = 0.7;
  float radius = 0.5;
  float sphere_diameter = 0.139;
  glm::vec3 current_pose = vec3(0, 0, 0);

  //---------------------------
};

}