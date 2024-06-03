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
  //Main functions
  utl::base::Element* import(utl::media::Path path);

private:
  //Header
  void parse_header(std::ifstream& file);
  void parse_header_format(std::string format);
  void parse_header_property(std::string type, std::string field);

private:
  format::ply::importer::Ascii* ply_ascii;
  format::ply::importer::Binary* ply_binary;

  std::vector<format::ply::Property> vec_property;
  int file_format;
  int point_data_idx;
  int point_number;
  int face_number;
  int header_size;
};

}
