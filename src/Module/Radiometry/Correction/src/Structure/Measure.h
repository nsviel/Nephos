#pragma once

#include <Utility/Base/Data/Path.h>
#include <string>
#include <vector>


namespace rad::cor::structure{

struct Measure{
  //---------------------------

  //General
  std::string mode = "NFOV";
  utl::base::Path path;

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
