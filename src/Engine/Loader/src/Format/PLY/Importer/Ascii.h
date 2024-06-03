#pragma once

#include <Loader/src/Format/PLY/Utils.h>
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


namespace format::ply{

class Ascii
{
public:
  //Constructor / Destructor
  Ascii();
  ~Ascii();

public:
  //Main function
  void parse_ascii(std::ifstream& file, utl::file::Data* entity);
  void parse_ascii_withface(std::ifstream& file, utl::file::Data* entity);

private:
  std::vector<format::ply::Property> vec_property;
};

}
