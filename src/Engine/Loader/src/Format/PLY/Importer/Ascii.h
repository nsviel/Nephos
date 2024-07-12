#pragma once

#include <Loader/src/Format/PLY/Structure/Namespace.h>
#include <Loader/src/Base/Importer.h>
#include <Utility/Function/File/Path.h>
#include <Utility/Function/Math/Math.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <stdint.h>
#include <cstdint>


namespace format::ply::importer{

class Ascii
{
public:
  //Constructor / Destructor
  Ascii();
  ~Ascii();

public:
  //Main function
  void parse_ascii(dat::base::Object* object, format::ply::Header* header);

  //Parser
  void parse_vertex(std::ifstream& file);
  void parse_face(std::ifstream& file);

  //Subfunction
  void pass_header(std::ifstream& file);
  int get_property_id(format::ply::Field field);

private:
  format::ply::Header* header = nullptr;
  utl::base::Data data;
};

}
