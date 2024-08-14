#pragma once

#include <Importer/src/Structure/Enum.h>
#include <Importer/src/Structure/Property.h>
#include <Utility/Namespace.h>
#include <vector>
#include <string>


namespace io::imp{

struct Configuration{
  //---------------------------

  io::imp::Encoding encoding = io::imp::ASCII;
  utl::topology::Type topology = utl::topology::POINT;
  std::vector<io::imp::Property> vec_property;
  std::string path = "";
  bool has_header = true;
  int nb_property = 0;
  int nb_vertex = 0;
  int nb_face = 0;

  //---------------------------
};

}
