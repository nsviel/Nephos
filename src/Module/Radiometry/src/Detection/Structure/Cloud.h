#pragma once


namespace rad::detection::structure{

struct Ransac{
  //---------------------------

  int nb_iter = 1000;
  float thres_sphere = 0.005;
  float thres_pose = 0.1;
  float thres_radius = 0.02;
  float search_diameter_x = 0.7;
  glm::vec3 current_pose = vec3(0, 0, 0);

  //---------------------------
};

struct Sphere{
  //---------------------------

  float diameter;
  glm::vec3 center;
  glm::vec3 pose;

  //---------------------------
};

}
