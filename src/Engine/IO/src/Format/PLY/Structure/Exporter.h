#pragma once

#include <IO/src/Format/PLY/Structure/Enum.h>
#include <glm/glm.hpp>
#include <vector>
#include <string>


namespace fmt::ply::exporter{

struct Structure{
  std::vector<fmt::ply::Field> vec_property;
  std::string encoding = "";
  std::string path = "";
  glm::mat4 mat_model;
  glm::mat3 mat_rotation;
  int nb_property = 0;
  int nb_vertex = 0;
};

}
