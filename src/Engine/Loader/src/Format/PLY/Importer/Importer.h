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

namespace format::ply::importer{class Ascii;}
namespace format::ply::importer{class Binary;}


namespace format::ply{

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
  void parse_header(std::string path);
  void parse_header_format(std::string format);
  void parse_header_property(std::string type, std::string field);

private:
  format::ply::importer::Ascii* ply_ascii;
  format::ply::importer::Binary* ply_binary;

  format::ply::Header header;
};

}
