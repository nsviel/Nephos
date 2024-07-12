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

namespace fmt::ply::importer{class Ascii;}
namespace fmt::ply::importer{class Binary;}


namespace fmt::ply{

class Importer : public ldr::base::Importer
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
  bool parse_header(std::string path);
  void parse_header_format(std::string format);
  void parse_header_property(std::string type, std::string field);
  bool parse_header_size(std::string nb_vertex);

private:
  fmt::ply::importer::Ascii* ply_ascii;
  fmt::ply::importer::Binary* ply_binary;

  fmt::ply::Header header;
};

}
