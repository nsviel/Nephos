#pragma once

#include <Loader/src/Format/PLY/Structure/Enum.h>
#include <vector>
#include <string>


namespace fmt::ply::exporter{

struct Structure{
  fmt::ply::Encoding encoding = fmt::ply::ASCII;
  std::vector<fmt::ply::Field> vec_property;
  int nb_property = 0;
  int nb_vertex = 0;
};

}
