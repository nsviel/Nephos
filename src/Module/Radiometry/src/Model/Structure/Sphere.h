#pragma once

#include <string>
#include <vector>


namespace rad::model::structure{

struct Sphere{
  //---------------------------

  //General
  std::string path = "../media/record/calibration/sphere.data";
  int state_step = rad::detection::VALIDATION;
  int state_data = rad::detection::NO_DATA;

  //Data
  std::vector<glm::vec3> data;
  int size = 0;

  //R
  glm::vec2 R_range = glm::vec2(0, 0);
  float R_resolution = 0;
  int R_size = 0;

  //It
  glm::vec2 It_range = glm::vec2(0, 0);
  float It_resolution = 0;
  int It_size = 0;

  //I
  glm::vec2 I_range = glm::vec2(0, 0);

  //---------------------------
};

}
