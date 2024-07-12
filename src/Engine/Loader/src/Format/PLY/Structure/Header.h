#pragma once

#include <Loader/src/Format/PLY/Structure/Property.h>
#include <Utility/Namespace.h>
#include <vector>
#include <string>


namespace fmt::ply{

enum Encoding{
  ASCII = 0,
  BINARY_LITTLE_ENDIAN = 1,
  BINARY_BIG_ENDIAN = 2,
};

struct Header{
  fmt::ply::Encoding encoding = fmt::ply::ASCII;
  utl::topology::Type topology = utl::topology::POINT;
  std::vector<fmt::ply::Property> vec_property;
  std::string path = "";
  int nb_property = 0;
  int nb_vertex = 0;
  int nb_face = 0;
};

}
