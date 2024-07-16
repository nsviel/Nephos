#pragma once

#include <IO/src/Import/Structure/Base.h>
#include <IO/src/Import/Structure/Buffer.h>
#include <IO/src/Import/Structure/Configuration.h>
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
  void parse_ascii(io::importer::Configuration* ply_struct, dat::base::Object* object);

  //Subfunction
  void pass_header(std::ifstream& file);
  void parse_vertex(io::importer::Configuration* ply_struct, std::ifstream& file);
  void parse_face(io::importer::Configuration* ply_struct, std::ifstream& file);
  int get_property_id(io::importer::Configuration* ply_struct, io::importer::Field field);

private:
  utl::base::Attribut* utl_attribut;

  io::importer::Buffer buffer;
};

}
