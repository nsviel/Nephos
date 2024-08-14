#pragma once

#include <Importer/src/Structure/Base.h>
#include <Importer/src/Structure/Buffer.h>
#include <Importer/src/Structure/Configuration.h>
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
  void parse_ascii(io::imp::Configuration* config, dat::base::Object* object);

  //Subfunction
  void pass_header(std::ifstream& file);
  void parse_vertex(io::imp::Configuration* config, std::ifstream& file);
  void parse_face(io::imp::Configuration* config, std::ifstream& file);
  int get_property_id(io::imp::Configuration* config, io::imp::Field field);

private:
  utl::base::Attribut* utl_attribut;

  io::imp::Buffer buffer;
};

}
