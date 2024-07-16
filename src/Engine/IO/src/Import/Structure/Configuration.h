#pragma once

#include <IO/src/Format/PLY/Structure/Enum.h>
#include <IO/src/Import/Structure/Property.h>
#include <Utility/Namespace.h>
#include <vector>
#include <string>


namespace io::importer{

struct Configuration{
  fmt::ply::Encoding encoding = fmt::ply::ASCII;
  utl::topology::Type topology = utl::topology::POINT;
  std::vector<io::importer::Property> vec_property;
  std::string path = "";
  int nb_property = 0;
  int nb_vertex = 0;
  int nb_face = 0;
};

}
