#pragma once

#include <IO/src/Format/PLY/Structure/Namespace.h>
#include <IO/src/Import/Structure/Base.h>
#include <Utility/Function/File/Path.h>
#include <Utility/Function/Math/Math.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <stdint.h>
#include <cstdint>

namespace fmt::ply::importer{class Ascii;}
namespace fmt::ply::importer{class Binary;}


namespace fmt::ply{

class Importer : public ldr::importer::Base
{
public:
  //Constructor / Destructor
  Importer();
  ~Importer();

public:
  //Main function
  utl::base::Element* import(utl::base::Path path);

private:
  //Header
  bool parse_header(fmt::ply::importer::Structure& ply_struct);
  void parse_header_format(fmt::ply::importer::Structure& ply_struct, std::string format);
  bool parse_header_size(fmt::ply::importer::Structure& ply_struct, std::string nb_vertex);
  void parse_header_property(fmt::ply::importer::Structure& ply_struct, std::string type, std::string field);

private:
  fmt::ply::importer::Ascii* ply_ascii;
  fmt::ply::importer::Binary* ply_binary;
};

}
