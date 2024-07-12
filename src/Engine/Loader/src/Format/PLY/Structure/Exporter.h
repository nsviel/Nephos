#pragma once

#include <Loader/src/Format/PLY/Structure/Enum.h>
#include <glm/glm.hpp>
#include <vector>
#include <string>


namespace fmt::ply::exporter{

struct Structure{
  glm::mat4 mat;
  std::vector<fmt::ply::Field> vec_property;
  std::string encoding = "";
  int nb_property = 0;
  int nb_vertex = 0;
};

}
