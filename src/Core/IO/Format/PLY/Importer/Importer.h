#pragma once

#include <Importer/src/Structure/Configuration.h>
#include <IO/Base/Importer.h>
#include <Utility/Function/File/Path.h>
#include <Utility/Function/Math/Operation.h>
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

class Importer : public io::base::Importer
{
public:
  //Constructor / Destructor
  Importer();
  ~Importer();

public:
  //Main function
  std::shared_ptr<utl::base::Element> import(utl::base::Path path);

private:
  //Header
  bool parse_header(io::imp::Configuration& config);
  void parse_header_format(io::imp::Configuration& config, std::string format);
  bool parse_header_size(io::imp::Configuration& config, std::string nb_vertex);
  void parse_header_property(io::imp::Configuration& config, std::string type, std::string field);

private:
  fmt::ply::importer::Ascii* ply_ascii;
  fmt::ply::importer::Binary* ply_binary;
};

}
