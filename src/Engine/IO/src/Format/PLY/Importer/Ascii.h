#pragma once

#include <IO/src/Format/PLY/Structure/Namespace.h>
#include <IO/src/Import/Structure/Base.h>
#include <IO/src/Import/Structure/Buffer.h>
#include <Utility/Function/File/Path.h>
#include <Utility/Function/Math/Operation.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <stdint.h>
#include <cstdint>

namespace utl::base{class Attribut;}


namespace fmt::ply::importer{

class Ascii
{
public:
  //Constructor / Destructor
  Ascii();
  ~Ascii();

public:
  //Main function
  void parse_ascii(fmt::ply::importer::Structure* ply_struct, dat::base::Object* object);

  //Subfunction
  void pass_header(std::ifstream& file);
  void parse_vertex(fmt::ply::importer::Structure* ply_struct, std::ifstream& file);
  void parse_face(fmt::ply::importer::Structure* ply_struct, std::ifstream& file);
  int get_property_id(fmt::ply::importer::Structure* ply_struct, fmt::ply::Field field);

private:
  utl::base::Attribut* utl_attribut;

  io::importer::Buffer buffer;
};

}
