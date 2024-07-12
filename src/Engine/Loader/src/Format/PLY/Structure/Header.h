#pragma once

#include <Utility/Namespace.h>
#include <string>


namespace format::ply{

enum Encoding{
  ASCII = 0,
  BINARY_LITTLE_ENDIAN = 1,
  BINARY_BIG_ENDIAN = 2,
};

struct Header{
  format::ply::Encoding encoding = format::ply::ASCII;
  utl::topology::Type topology = utl::topology::POINT;
  std::vector<format::ply::Property> vec_property;
  std::string path = "";
  int nb_vertex = 0;
  int nb_face = 0;
};

}
